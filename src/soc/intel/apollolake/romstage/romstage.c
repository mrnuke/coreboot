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
#include <fsp/util.h>
#include <device/resource.h>
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

/*
 * Now that FSP is done consuming large amounts of CAR, we can use a much
 * larger portion of CAR for the stack. The larger stack is needed for
 * decompressing ramstage. It turns out that setting the stack pointer to top
 * of CAR gives us the largest uninterrupted stack.
 */
static void *realloc_stack(void)
{
	uintptr_t new_stack = CONFIG_DCACHE_RAM_BASE + CONFIG_DCACHE_RAM_SIZE;
	new_stack -= sizeof(size_t);
	printk(BIOS_DEBUG, "Placing new stack at 0x%lx\n", new_stack);
	return (void *)new_stack;
}

asmlinkage void* romstage_entry(void)
{
	void *hob_list_ptr;
	struct resource fsp_mem;

	/* Be careful. Bootblock might already have initialized the console */
	if (!IS_ENABLED(CONFIG_BOOTBLOCK_CONSOLE)) {
		lpss_console_uart_init();
		console_init();
	}

	printk(BIOS_DEBUG, "Starting romstage...\n");

	soc_early_romstage_init();

	fsp_memory_init(&hob_list_ptr, cbmem_overhead_size());

	fsp_find_reserved_memory(&fsp_mem, hob_list_ptr);

	/* initialize cbmem by adding FSP reserved memory first thing */
	cbmem_initialize_empty_id_size(CBMEM_ID_FSP_RESERVED_MEMORY,
					fsp_mem.size);

	/* make sure FSP memory is reserved in cbmem */
	if (fsp_mem.base != (uintptr_t)cbmem_find(CBMEM_ID_FSP_RESERVED_MEMORY))
		die("Failed to accommodate FSP reserved memory request");

	return realloc_stack();
}

asmlinkage void romstage_after_raminit(void)
{
	run_ramstage();
}

void platform_fsp_memory_init_params_cb(struct MEMORY_INIT_UPD *memupd)
{
        mainboard_memory_init_params(memupd);
}

__attribute__ ((weak))
void mainboard_memory_init_params(struct MEMORY_INIT_UPD *memupd)
{
        printk(BIOS_DEBUG, "WEAK: %s/%s called\n", __FILE__, __func__);
}
