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
#include <console/console.h>
#include <device/pci.h>
#include <soc/bootblock.h>
#include <soc/uart.h>

static void disable_watchdog(void)
{
	uint32_t reg;
	device_t dev = PCI_DEV(0, 0xd, 1);

	/* Open up an IO window */
	pci_write_config16(dev, PCI_BASE_ADDRESS_4, 0x400);
	pci_write_config32(dev, PCI_COMMAND,
			   PCI_COMMAND_MASTER | PCI_COMMAND_IO);

	/* We don't have documentation for this bit, but it prevents reboots */
	reg = inl(0x400 + 0x68);
	reg |= 1 << 11;
	outl(reg, 0x400 + 0x68);
}

void bootblock_car_main(void)
{
	/* Quick post code to show we made it to C code */
	outb(0x30, 0x80);

	if (IS_ENABLED(CONFIG_BOOTBLOCK_CONSOLE)) {
		lpss_console_uart_init();
		console_init();
	}

	/* Wait until after we have console to disable this */
	disable_watchdog();

	/* Don't return, so we see the above post code */
	while (1)
		;
}
