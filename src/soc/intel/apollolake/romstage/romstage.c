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
#include <soc/romstage.h>
#include <soc/uart.h>

asmlinkage void romstage_entry(void)
{
	/* Be careful. Bootblock might already have initialized the console */
	if (!IS_ENABLED(CONFIG_BOOTBLOCK_CONSOLE)) {
		lpss_console_uart_init();
		console_init();
	}

	printk(BIOS_DEBUG, "Starting romstage...\n");

	/* This function must not return */
	while(1)
		;
}
