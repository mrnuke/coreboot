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

#ifndef _FSP2_0_UTIL_H_
#define _FSP2_0_UTIL_H_

#include <fsp/info_header.h>

/* Load an FSP binary into CBFS, and fill the associated fsp_header struct */
enum cb_err fsp_load_binary(struct fsp_header *hdr, const char *name);

#endif /* _FSP2_0_UTIL_H_ */
