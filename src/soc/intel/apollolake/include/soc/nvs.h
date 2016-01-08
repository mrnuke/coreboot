/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Lance Zhao <lijian.zhao@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _SOC_APOLLOLAKE_NVS_H_
#define _SOC_APOLLOLAKE_NVS_H_

#include <vendorcode/google/chromeos/gnvs.h>

struct global_nvs_t {
	/* Miscellaneous */
	uint8_t unused[256];

	/* ChromeOS specific (0x100 - 0xfff) */
	chromeos_acpi_t chromeos;
} __attribute__((packed));

#endif	/* _SOC_APOLLOLAKE_NVS_H_ */
