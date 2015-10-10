/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Alexandru Gagniuc <mr.nuke.me@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <arch/cpu.h>
#include <cbfs.h>
#include <halt.h>

/* Called from assembly. Prototype not needed by external .c file */
asmlinkage void bootblock_main(uint32_t bist, uint32_t tsc_lo, uint32_t tsc_hi);

/*
 * TODO: Implement a generic fallback/normal mechanism
 */
static const char *get_next_stage_name(void)
{
	if (IS_ENABLED(CONFIG_BOOTBLOCK_SIMPLE))
		return CONFIG_CBFS_PREFIX "/romstage";

	/* BOOTBLOCK_NORMAL not implemented */
	return CONFIG_CBFS_PREFIX "/romstage";
}

static void enter_romstage(void *romstage_entry, uint32_t bist)
{
	asm volatile (
		"jmp *%0\n\t"
		: : "r" (romstage_entry), "a" (bist)
	);
}

asmlinkage void bootblock_main(uint32_t bist, uint32_t tsc_lo, uint32_t tsc_hi)
{
	void *entry;
	struct cbfs_stage *romstage;
	const char* target1 = get_next_stage_name();

	romstage = cbfs_boot_map_with_leak(target1, CBFS_TYPE_STAGE, NULL);

	/*
	 * TODO: Do something constructive with tsc_lo and tsc_hi
	 */
	if (romstage) {
		entry = (void *)(uintptr_t)romstage->entry;
		enter_romstage(entry, bist);
	}
	halt();
}
