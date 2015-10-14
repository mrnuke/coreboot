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

#include <boot_device.h>
#include <console/console.h>
#include <cbfs.h>
#include <endian.h>
#include <stdlib.h>
#include <commonlib/region.h>
#include <fmap.h>

/*
 *  If Apollo Lake is configured to boot from SPI flash "BIOS" region
 *  (as defined in descriptor) is mapped below 4GiB.  Form a pointer for
 *  the base.
 */
#define ROM_BASE ((void *)(uintptr_t)(0x100000000ULL - CONFIG_IFD_BIOS_SIZE))

static const struct mem_region_device boot_dev = {
	.base = (void *) ROM_BASE,
	/* typically not whole flash is memory mapped */
	.rdev = REGION_DEV_INIT(&mem_rdev_ops, CONFIG_IFD_BIOS_START,
							CONFIG_IFD_BIOS_SIZE)
};

const struct region_device *boot_device_ro(void)
{
	return &boot_dev.rdev;
}

static int iafw_boot_region_properties(struct cbfs_props *props)
{
	struct region regn;

	/* use fmap to locate CBFS area */
	if (fmap_locate_area("COREBOOT", &regn))
		return 1;

	props->offset = regn.offset;
	props->size = regn.size;

	printk(BIOS_DEBUG, "CBFS @ %zx size %zx\n", props->offset, props->size);

	return 0;
}

/*
 * Named cbfs_master_header_locator so that it overrides the default, but
 * incompatible locator in cbfs.c
 */
const struct cbfs_locator cbfs_master_header_locator = {
	.name = "IAFW Locator",
	.locate = iafw_boot_region_properties,
};
