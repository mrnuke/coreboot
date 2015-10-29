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

#ifndef _FSP2_0_INFO_HEADER_H_
#define _FSP2_0_INFO_HEADER_H_

#include <stdint.h>
#include <stdlib.h>
#include <types.h>

#define FSP_HDR_OFFSET			0x94
#define FSP_HDR_LEN			0x48
#define FSP_HDR_SIGNATURE		"FSPH"

struct fsp_header {
	uint32_t fsp_revision;
	size_t image_size;
	uintptr_t image_base;
	size_t cfg_region_offset;
	size_t cfg_region_size;
	size_t notify_phase_entry_offset;
	size_t memory_init_entry_offset;
	size_t silicon_init_entry_offset;
	char image_id[9];
	uint8_t revision;
};

enum cb_err fsp_identify(struct fsp_header *hdr, const void *fsp_blob);
void fsp_print_header_info(const struct fsp_header *hdr);

#endif /* _FSP2_0_INFO_HEADER_H_ */
