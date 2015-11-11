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

#include <arch/cpu.h>
#include <console/console.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <string.h>

typedef asmlinkage enum fsp_status (*fsp_silicon_init_fn)
				   (struct SILICON_INIT_UPD *upd);


static enum fsp_status do_silicon_init(struct fsp_header *hdr)
{
	struct SILICON_INIT_UPD silicon_upd, *upd_region;
	fsp_silicon_init_fn silicon_init;
	enum fsp_status status;

	upd_region = (void*)(hdr->cfg_region_offset + hdr->image_base);

	/* populate upd with defaults */
	silicon_upd = *upd_region;

	silicon_init = (void *)(hdr->image_base + hdr->silicon_init_entry_offset);

	/* give a chance to populate entries */
	platform_fsp_silicon_init_params_cb(&silicon_upd);

	status = silicon_init(&silicon_upd);
	printk(BIOS_DEBUG, "FspSiliconInit returned 0x%08x\n", status);
	return status;
}

enum fsp_status fsp_silicon_init(void)
{
	struct fsp_header hdr;

	if (fsp_load_binary(&hdr, "blobs/fsp-s.bin") != CB_SUCCESS)
		return FSP_NOT_FOUND;

	return do_silicon_init(&hdr);
}

__attribute__((weak))
void platform_fsp_silicon_init_params_cb(struct SILICON_INIT_UPD *silupd)
{
	printk(BIOS_DEBUG, "WEAK: %s called\n", __func__);
}
