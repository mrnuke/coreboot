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

	/*
	 * eax contains pointer to a region in RAM that we've been given the go
	 * ahead to use as stack. The old stack is empty at this point, so we
	 * don't have to relocate anything.
	 */
	mov	esp, eax

	/*
	 * TODO: set up temporary cache for RAM
	 * We can't tear down CAR yet because romstage resides in CAR.
	 */
	call	romstage_after_raminit
