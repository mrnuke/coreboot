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

#include <console/console.h>
#include <fsp/util.h>

void lb_framebuffer(struct lb_header *header)
{
	enum cb_err ret;
	struct lb_framebuffer *framebuffer;

	framebuffer = (void *)lb_new_record(header);
	ret = fsp_fill_lb_framebuffer(framebuffer);
	if (ret != CB_SUCCESS)
		printk(BIOS_ALERT, "FSP did not return a valid framebuffer\n");
}
