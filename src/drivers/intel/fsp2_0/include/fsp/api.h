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

#ifndef _FSP2_0_API_H_
#define _FSP2_0_API_H_

#include "FspUpdVpd.h"

enum fsp_status {
	FSP_SUCCESS = 0x00000000,
	FSP_INVALID_PARAMETER = 0x80000002,
	FSP_UNSUPPORTED = 0x80000003,
	FSP_NOT_READY = 0x80000006,
	FSP_DEVICE_ERROR = 0x80000007,
	FSP_OUT_OF_RESOURCES = 0x80000009,
	FSP_VOLUME_CORRUPTED = 0x8000000a,
	FSP_NOT_FOUND = 0x8000000a,
	FSP_TIMEOUT = 0x80000012,
	FSP_ABORTED = 0x80000015,
	FSP_INCOMPATIBLE_VERSION = 0x80000010,
	FSP_SECURITY_VIOLATION = 0x8000001a,
	FSP_CRC_ERROR = 0x8000001b,
};

/* Main FSP stages */
enum fsp_status fsp_memory_init(void);
enum fsp_status fsp_silicon_init(void);
enum fsp_status fsp_notify(void);

/* Callbacks for updating stage-specific parameters */
void platform_fsp_memory_init_params_cb(struct MEMORY_INIT_UPD *memupd);
void platform_fsp_silicon_init_params_cb(struct SILICON_INIT_UPD *silupd);

#endif /* _FSP2_0_API_H_ */
