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

#include <cpu/cpu.h>
#include <device/device.h>
#include <device/pci.h>
#include <soc/cpu.h>

static void cpu_core_init(device_t cpu)
{
}

static struct device_operations cpu_dev_ops = {
	.init = cpu_core_init,
};

static struct cpu_device_id cpu_table[] = {
	{ X86_VENDOR_INTEL, CPUID_APOLLOLAKE_A0 },
	{ 0, 0 },
};

static const struct cpu_driver driver __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
