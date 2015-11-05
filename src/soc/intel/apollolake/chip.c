/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <cpu/cpu.h>
#include <device/device.h>
#include <device/pci.h>

static struct device_operations pci_domain_ops = {
	.read_resources = pci_domain_read_resources,
	.set_resources = DEVICE_NOOP,
	.enable_resources = NULL,
	.init = NULL,
	.scan_bus = pci_domain_scan_bus,
	.ops_pci_bus = pci_bus_default_ops,
};

static void cpu_bus_init(device_t dev)
{
	initialize_cpus(dev->link_list);
}

static struct device_operations cpu_bus_ops = {
	.read_resources = DEVICE_NOOP,
	.set_resources = DEVICE_NOOP,
	.enable_resources = DEVICE_NOOP,
	.init = cpu_bus_init,
	.scan_bus = 0,
};

static void enable_dev(device_t dev)
{
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN) {
		dev->ops = &pci_domain_ops;
	} else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER) {
		dev->ops = &cpu_bus_ops;
	}
}

struct chip_operations soc_intel_apollolake_ops = {
	CHIP_NAME("Intel Apollolake SOC")
	.enable_dev = &enable_dev,
};
