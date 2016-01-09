/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2004 Stefan Reinauer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <device/pci_def.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <pc80/mc146818rtc.h>
#include <console/console.h>
#include <timestamp.h>
#include "drivers/pc80/udelay_io.c"
#include <delay.h>
#include <cpu/x86/lapic.h>

#include "memory.c"

#include <cpu/qemu-x86/romstage.h>
void main(void)
{
	int cbmem_was_initted;

	/* init_timer(); */
	post_code(0x05);

	console_init();

	//print_pci_devices();
	//dump_pci_devices();

	cbmem_was_initted = !cbmem_recovery(0);

	timestamp_init(timestamp_get());
	timestamp_add_now(TS_START_ROMSTAGE);

}
