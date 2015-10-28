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

.intel_syntax noprefix
apollolake_entry:

	/*
	 * TODO: Make sure the stack does not clash with .car.data.
	 */
	mov	esp, (CONFIG_DCACHE_RAM_BASE + 0x4000)

	call	romstage_entry
