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

#include <arch/io.h>
#include <soc/bootblock.h>

void bootblock_car_main(void)
{
	/* Quick post code to show we made it to C code */
	outb(0x30, 0x80);
	/* Don't return, so we see the above post code */
	while (1)
		;
}
