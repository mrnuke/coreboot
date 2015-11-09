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
#include <cbmem.h>
#include <console/console.h>
#include <cpu/x86/msr.h>
#include <device/pci_def.h>
#include <fsp/api.h>
#include <soc/iomap.h>
#include <soc/romstage.h>
#include <soc/uart.h>

/*
 * Enables several BARs and devices which are needed for memory init
 * - MCH_BASE_ADDR is needed in order to talk to the memory controller
 * - PMC_BAR0 and PMC_BAR1 are used by FSP (with the base address hardcoded)
 *   Once raminit is done, we can safely let the allocator re-assign them
 * - HPET is enabled because FSP wants to store a pointer to global data in the
 *   HPET comparator register
 */
static void soc_early_romstage_init(void)
{
	msr_t msr;
	device_t pmc = PCI_DEV(0, 13, 1);

	/* Set MCH base address and enable bit */
	pci_write_config32(PCI_DEV(0, 0, 0), 0x48, MCH_BASE_ADDR | 1);

	/* Set PMC base address */
	pci_write_config32(pmc, PCI_BASE_ADDRESS_0, PMC_BAR0);
	pci_write_config32(pmc, PCI_BASE_ADDRESS_1, 0);	/* 64-bit BAR */
	pci_write_config32(pmc, PCI_BASE_ADDRESS_2, PMC_BAR1);
	pci_write_config32(pmc, PCI_BASE_ADDRESS_3, 0);	/* 64-bit BAR */

	/* PMIO BAR4 was already set in bootblock, hence the COMMAND_IO below */
	pci_write_config32(pmc, PCI_COMMAND,
				PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
				PCI_COMMAND_MASTER);

	/* Enable decoding for HPET */
	pci_write_config32(PCI_DEV(0, 13, 0), 0x60, 1<<7);
}

static void *alloc_stack_in_ram(void)
{
	uint8_t *ram_stack = cbmem_add(CBMEM_ID_ROMSTAGE_RAM_STACK,
				    CONFIG_ROMSTAGE_RAM_STACK_SIZE);

	/*
	 * If cbmem fails to give us a memory window, try to get a stack at
	 * 2 MiB, and hope we can go forward. The 2 MiB address is arbitrary.
	 */
	if (ram_stack == NULL) {
		printk(BIOS_ALERT, "Could not find place for stack\n");
		return (void *)(2 * MiB);
	}

	/* The initial stack pointer should point at the top of the region */
	ram_stack += CONFIG_ROMSTAGE_RAM_STACK_SIZE - sizeof(size_t);
	return ram_stack;
}

asmlinkage void* romstage_entry(void)
{
	void *hob_list_ptr;
	/* Be careful. Bootblock might already have initialized the console */
	if (!IS_ENABLED(CONFIG_BOOTBLOCK_CONSOLE)) {
		lpss_console_uart_init();
		console_init();
	}

	printk(BIOS_DEBUG, "Starting romstage...\n");

	soc_early_romstage_init();

	fsp_memory_init(&hob_list_ptr);

	cbmem_initialize_empty();
	return alloc_stack_in_ram();
}

asmlinkage void romstage_after_raminit(void)
{
	run_ramstage();
}
