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
#include <bootblock_common.h>
#include <cbfs.h>
#include <console/console.h>
#include <cpu/x86/bist.h>
#include <halt.h>

/* Called from assembly. Prototype not needed by external .c file */
asmlinkage void bootblock_main(uint32_t bist, uint32_t tsc_lo, uint32_t tsc_hi);

asmlinkage void bootblock_main(uint32_t bist, uint32_t tsc_lo, uint32_t tsc_hi)
{
	/*
	 * TODO: We might want a cleaner way to handle BIST reporting before we
	 * can converge with the generic bootblock in lib/.
	 */
	report_bist_failure(bist);

	/* Now jump to the generic bootblock and be on your merry way. */
	main();
}
