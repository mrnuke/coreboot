/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Andrey Petrov <andrey.petrov@intel.com> for Intel Corp.)
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <arch/io.h>
#include <arch/cpu.h>
#include <console/console.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <string.h>
#include <timestamp.h>

#define FIT_POINTER		(0x100000000ULL - 0x40)
#define FIT_SIZE		0x400

struct fsp_memory_init_params {
	void *nvs_buffer;
	void *rt_buffer;
	void **hob_list;
} __attribute__ ((__packed__));

struct fsp_init_rt_common_buffer {
	void *stack_top;
	uint32_t boot_mode;
	void *upd_data_rgn;
	uint32_t bootloader_tolum_size;
} __attribute__ ((__packed__));

typedef asmlinkage enum fsp_status (*fsp_memory_init_fn)
				   (struct fsp_memory_init_params *);

static void fill_console_params(struct MEMORY_INIT_UPD *memupd)
{
	if (IS_ENABLED(CONFIG_CONSOLE_SERIAL)) {
		memupd->SerialDebugPortDevice = CONFIG_UART_FOR_CONSOLE;
		memupd->SerialDebugPortType = 2;
		memupd->SerialDebugPortStrideSize = 2;
		memupd->SerialDebugPortAddress = 0;
	} else {
		memupd->SerialDebugPortType = 0;
	}
}

__attribute__((weak))
void platform_fsp_memory_init_params_cb(struct MEMORY_INIT_UPD *memupd)
{
	printk(BIOS_DEBUG, "WEAK: %s called\n", __func__);
}

static enum fsp_status do_fsp_memory_init(void **hob_list_ptr,
					  struct fsp_header *hdr,
					  size_t tolum_size)
{
	enum fsp_status status;
	fsp_memory_init_fn fsp_raminit;
	struct fsp_memory_init_params raminit_params;
	struct fsp_init_rt_common_buffer rt_buffer;
	struct MEMORY_INIT_UPD raminit_upd, *upd_region;

	post_code(0x34);
	upd_region = (void*)(hdr->cfg_region_offset + hdr->image_base);
	raminit_upd = *upd_region;

	/* Zero fill RT Buffer data and start populating fields. */
	memset(&rt_buffer, 0, sizeof(rt_buffer));

	rt_buffer.upd_data_rgn = &raminit_upd;
	rt_buffer.bootloader_tolum_size = tolum_size;

	/* Get any board specific changes */
	raminit_params.nvs_buffer = NULL;
	raminit_params.rt_buffer = &rt_buffer;
	raminit_params.hob_list = hob_list_ptr;

	/* Update the UPD data */
	raminit_upd.GpioPadInitTablePtr = NULL;
	raminit_upd.FitTablePtr = read32((void *)FIT_POINTER);
	fill_console_params(&raminit_upd);
	platform_fsp_memory_init_params_cb(&raminit_upd);

	/* Call FspMemoryInit */
	fsp_raminit = (void *)(hdr->image_base + hdr->memory_init_entry_offset);
	printk(BIOS_DEBUG, "Calling FspMemoryInit: 0x%p\n", fsp_raminit);
	printk(BIOS_SPEW, "\t%p: nvs_buffer\n", raminit_params.nvs_buffer);
	printk(BIOS_SPEW, "\t%p: rt_buffer\n", raminit_params.rt_buffer);
	printk(BIOS_SPEW, "\t%p: hob_list\n", raminit_params.hob_list);

	timestamp_add_now(TS_FSP_MEMORY_INIT_START);
	status = fsp_raminit(&raminit_params);
	post_code(0x37);
	timestamp_add_now(TS_FSP_MEMORY_INIT_END);

	printk(BIOS_DEBUG, "FspMemoryInit returned 0x%08x\n", status);

	return status;
}

enum fsp_status fsp_memory_init(void **hob_list, size_t tolum_size)
{
	struct fsp_header hdr;

	if (fsp_load_binary(&hdr, "blobs/fsp-m.bin") != CB_SUCCESS)
		return FSP_NOT_FOUND;

	return do_fsp_memory_init(hob_list, &hdr, tolum_size);
}
