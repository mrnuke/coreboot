/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Andrey Petrov <andrey.petrov@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <console/console.h>
#include <soc/iomap.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <soc/northbridge.h>

static uint32_t get_bar(device_t dev, unsigned int index)
{
	uint32_t bar;

	bar = pci_read_config32(dev, index);

	/* If not enabled return 0 else strip enabled bit */
	return (bar & 1) ? (bar & ~1) : 0;
}

static int mc_add_fixed_mmio_resources(device_t dev, int index)
{
	struct resource *res;

	/* PCI extended config region */
	res = new_resource(dev, index++);
	res->flags = IORESOURCE_MEM | IORESOURCE_FIXED | IORESOURCE_STORED |
		     IORESOURCE_RESERVE | IORESOURCE_ASSIGNED;
	/* only last 4 bits encode BAR */
	res->base = get_bar(dev, PCIEXBAR) & 0xf0000000;
	res->size = PCIEX_SIZE;

	/* Memory Controller HUB */
	res = new_resource(dev, index++);
	res->flags = IORESOURCE_MEM | IORESOURCE_FIXED | IORESOURCE_STORED |
		     IORESOURCE_RESERVE | IORESOURCE_ASSIGNED;
	/* BITS 31:15 encode BAR */
	res->base = get_bar(dev, MCHBAR) & 0xffff8000;
	res->size = MCH_BASE_SIZE;
	return index;
}


static int mc_add_dram_resources(device_t dev, int index)
{
	unsigned long base_k, size_k;
	struct resource *resource;

	struct reserved_ram {
		uint32_t bgsm;
		uint32_t bdsm;
		uint32_t tolud;
		uint32_t tseg;
	} aplk_reserved_ram;

	aplk_reserved_ram.bgsm  = pci_read_config32(dev, BGSM);
	aplk_reserved_ram.bdsm  = pci_read_config32(dev, BDSM);
	aplk_reserved_ram.tolud = pci_read_config32(dev, TOLUD);
	aplk_reserved_ram.tseg  = pci_read_config32(dev, TSEG);

	/* 0 - > 0xa0000: 640kb of DOS memory. Not enough for anybody nowadays */
	ram_resource(dev, index++, 0, 640);

	/* 0xc0000 -> top_of_ram, skipping the legacy VGA region */
	base_k = 768;
	size_k = (aplk_reserved_ram.tseg >> 10) - base_k;
	ram_resource(dev, index++, base_k, size_k);

	/* TSEG -> BGSM */
	resource = new_resource(dev, index++);
	resource->base = aplk_reserved_ram.tseg;
	resource->size = aplk_reserved_ram.bgsm - resource->base;
	resource->flags = IORESOURCE_MEM | IORESOURCE_FIXED |
			  IORESOURCE_STORED | IORESOURCE_RESERVE |
			  IORESOURCE_ASSIGNED | IORESOURCE_CACHEABLE;

	/* BGSM -> BDSM */
	resource = new_resource(dev, index++);
	resource->base = aplk_reserved_ram.bgsm;
	resource->size = aplk_reserved_ram.bdsm - resource->base;
	resource->flags = IORESOURCE_MEM | IORESOURCE_FIXED |
			  IORESOURCE_STORED | IORESOURCE_RESERVE |
			  IORESOURCE_ASSIGNED;

	/* BDSM -> TOLUD */
	resource = new_resource(dev, index++);
	resource->base = aplk_reserved_ram.bdsm;
	resource->size = aplk_reserved_ram.tolud - resource->base;
	resource->flags = IORESOURCE_MEM | IORESOURCE_FIXED |
			  IORESOURCE_STORED | IORESOURCE_RESERVE |
			  IORESOURCE_ASSIGNED;

	/* 0xa0000 - 0xbffff: legacy VGA */
	mmio_resource(dev, index++, 640, 128);

	/* 0xe0000 - 0xfffff: PAM area */
	reserved_ram_resource(dev, index++, 768, 256);

	return index;
}

static void northbridge_read_resources(device_t dev)
{

	int index = 0;
	/* Read standard PCI resources. */
	pci_dev_read_resources(dev);

	/* Add all fixed MMIO resources. */
	index = mc_add_fixed_mmio_resources(dev, index);

	/* Calculate and add DRAM resources. */
	mc_add_dram_resources(dev, index);
}

static struct device_operations northbridge_ops = {
	.read_resources   = northbridge_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = DEVICE_NOOP,
	.enable           = DEVICE_NOOP
};

static const unsigned short northbridge_ids[] = {
	MCH_APOLLOLAKE_ID,
	0
};

static const struct pci_driver northbridge_driver __pci_driver = {
	.ops     = &northbridge_ops,
	.vendor  = PCI_VENDOR_ID_INTEL,
	.devices = northbridge_ids
};
