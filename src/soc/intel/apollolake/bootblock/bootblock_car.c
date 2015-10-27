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
#include <cbfs.h>
#include <console/console.h>
#include <device/pci.h>
#include <soc/bootblock.h>
#include <soc/cpu.h>
#include <soc/iomap.h>
#include <soc/uart.h>

static void disable_watchdog(void)
{
	uint32_t reg;
	device_t dev = PCI_DEV(0, 0xd, 1);

	/* Open up an IO window */
	pci_write_config16(dev, PCI_BASE_ADDRESS_4, ACPI_PMIO_BASE);
	pci_write_config32(dev, PCI_COMMAND,
			   PCI_COMMAND_MASTER | PCI_COMMAND_IO);

	/* We don't have documentation for this bit, but it prevents reboots */
	reg = inl(ACPI_PMIO_BASE + 0x68);
	reg |= 1 << 11;
	outl(reg, ACPI_PMIO_BASE + 0x68);
}

static void call_romstage(void *entry)
{
	__asm__ volatile (
		"call *%0"
		:: "r" (entry)
	);
}

void bootblock_car_main(void)
{
	void *romstage_entry;

	/* Quick post code to show we made it to C code */
	outb(0x30, 0x80);

	if (IS_ENABLED(CONFIG_BOOTBLOCK_CONSOLE)) {
		lpss_console_uart_init();
		console_init();
	}

	/* Wait until after we have console to disable this */
	disable_watchdog();

	romstage_entry = cbfs_boot_load_stage_by_name("fallback/romstage");
	if (!romstage_entry)
		die("romstage not found\n");

	/* APLK workaround: do this magic to keep cache executable on update */
	bxt_remark_cache_exec();

	/* Call the romstage entry point */
	call_romstage(romstage_entry);

	/* We should never reach this */
}
