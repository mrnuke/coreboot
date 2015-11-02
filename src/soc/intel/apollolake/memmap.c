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

#define TSEG 0xb8

#define __SIMPLE_DEVICE__
#include <arch/io.h>
#include <cbmem.h>

static uintptr_t smm_region_start(void)
{
	return pci_read_config32(PCI_DEV(0, 0, 0), TSEG) & (~1);
}

void *cbmem_top(void)
{
	return (void *)smm_region_start();
}
