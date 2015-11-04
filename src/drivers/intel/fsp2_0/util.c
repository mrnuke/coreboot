/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 * (Written by Andrey Petrov <andrey.petrov@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <arch/io.h>
#include <cbfs.h>
#include <console/console.h>
#include <fsp/util.h>
#include <lib.h>
#include <string.h>

static bool looks_like_fsp_header(const uint8_t *raw_hdr)
{
	if (memcmp(raw_hdr, FSP_HDR_SIGNATURE, 4)) {
		printk(BIOS_ALERT, "Did not find a valid FSP signature\n");
		return false;
	}

	if (read32(raw_hdr + 4) != FSP_HDR_LEN) {
		printk(BIOS_ALERT, "FSP header has invalid length\n");
		return false;
	}

	return true;
}

enum cb_err fsp_identify(struct fsp_header *hdr, const void *fsp_blob)
{
	const uint8_t *raw_hdr = fsp_blob;
	raw_hdr += FSP_HDR_OFFSET;

	if (!looks_like_fsp_header(raw_hdr))
		return CB_ERR;

	hdr->revision = read8(raw_hdr + 0x0b);
	hdr->fsp_revision = read32(raw_hdr + 0x0c);
	memcpy(hdr->image_id, raw_hdr + 0x10, 8);
	hdr->image_id[8] = '\0';
	hdr->image_size = read32(raw_hdr + 0x18);
	hdr->image_base = read32(raw_hdr + 0x1c);
	hdr->cfg_region_offset = read32(raw_hdr + 0x24);
	hdr->cfg_region_size = read32(raw_hdr + 0x28);
	hdr->notify_phase_entry_offset = read32(raw_hdr + 0x38);
	hdr->memory_init_entry_offset = read32(raw_hdr + 0x3c);
	hdr->silicon_init_entry_offset = read32(raw_hdr + 0x44);

	return CB_SUCCESS;
}

void fsp_print_header_info(const struct fsp_header *hdr)
{
	printk(BIOS_DEBUG, "Revision %u, image ID: %s, base 0x%lx + 0x%zx\n",
	       hdr->revision ,hdr->image_id, hdr->image_base, hdr->image_size);

	printk(BIOS_DEBUG, "\tConfig region        0x%zx + 0x%zx\n",
	       hdr->cfg_region_offset, hdr->cfg_region_size);
	printk(BIOS_DEBUG, "\tMemory init offset   0x%zx\n"
			   "\tSilicon init offset  0x%zx\n"
			   "\tNotify phase offset  0x%zx\n",
	       hdr->memory_init_entry_offset,
	       hdr->silicon_init_entry_offset,
	       hdr->notify_phase_entry_offset);
}

enum cb_err fsp_load_binary(struct fsp_header *hdr, const char *name)
{
	struct cbfsf file_desc;
	struct region_device file_data;
	size_t fsp_load_size;
	void *membase;

	if (cbfs_boot_locate(&file_desc, name, NULL)) {
		printk(BIOS_ERR, "Could not locate %s in CBFS\n", name);
		return CB_ERR;
	}

	cbfs_file_data(&file_data, &file_desc);

	/* Map just enough of the file to be able to parse the header. */
	membase = rdev_mmap(&file_data, 0, FSP_HDR_OFFSET + FSP_HDR_LEN);
	if (fsp_identify(hdr, membase) != CB_SUCCESS) {
		printk(BIOS_ERR, "%s did not have a valid FSP header\n", name);
		return CB_ERR;
	}

	fsp_print_header_info(hdr);

	/* Load binary into memory. */
	fsp_load_size = MIN(hdr->image_size, file_data.region.size);
	rdev_readat(&file_data, (void *)hdr->image_base, 0, fsp_load_size);

	return CB_SUCCESS;
}
