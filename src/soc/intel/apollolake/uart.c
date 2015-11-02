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

#include <console/uart.h>

/*
 * TODO: We need a mechanism to return the new BAR once the resource allocator
 * gives us a new location.
 */
uintptr_t uart_platform_base(int idx)
{
	return (CONFIG_CONSOLE_UART_BASE_ADDRESS);
}

unsigned int uart_platform_refclk(void)
{
	/* That's within 0.5% of the actual value we've set earlier */
	return 115200 * 16;
}
