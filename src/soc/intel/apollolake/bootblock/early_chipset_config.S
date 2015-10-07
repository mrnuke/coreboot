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

.intel_syntax noprefix
.extern cache_as_ram

#define post_code(value)	\
	mov	al, value;	\
	outb	CONFIG_POST_IO_PORT, al

.global bootblock_pre_c_entry
bootblock_pre_c_entry:
	/*
	 * eax:  BIST value
	 */
	movd	mm2, eax

	post_code(0x20)

enable_pciex_bar:
	mov	eax, 0x80000060		/* ROOT PCI device reg60 PCIEX_BAR_*/
	mov	dx, 0xcf8
	out	dx, eax
	mov	eax, (CONFIG_MMCONF_BASE_ADDRESS | 1)
	mov	dx, 0xcfc
	out	dx, eax

enable_iosf_bar:
	mov	ebp, 0xe0068000				/* IOSF PCI device */
	mov	dword ptr [ebp + 0x10], CONFIG_IOSF_BASE_ADDRESS /* BAR 0 */
	mov	word ptr [ebp + 0x04], 0x06		/* PCI command */


/* We need LPC for port80, but it won't work if the pads are not configured */
configure_lpc_pads:
	mov	ecx, offset num_lpc_pads /* Number of pads to configure */
	lea	esi, lpc_pad_params
init_lpc_pad:
	mov	edi, [esi + 0x00]	/* MMIO addr of pad config registers */
	mov	eax, [esi + 0x04]	/* Pad CONF0 value */
	mov	edx, [esi + 0x08]	/* Pad CONF1 value */
	mov	[edi + 0x00], eax	/* Write CONF0 to config register */
	mov	[edi + 0x04], edx	/* Write CONF1 to config register */
	add	esi, 0x0c
	loop	init_lpc_pad

	jmp	cache_as_ram

/* FIXME: Find a better way to define these */

#define LPC_CLKOUT0	0x118
#define LPC_CLKOUT1	0x120
#define LPC_AD0		0x128
#define LPC_AD1		0x130
#define LPC_AD2		0x138
#define LPC_AD3		0x140
#define LPC_CLKRUN	0x148
#define LPC_FRAME	0x150

#define XLATE_LPC(off)	((0xc0 << 16 ) | (0x500 + (off)))
#define PAD_MMIO_ADDR(poff)	CONFIG_IOSF_BASE_ADDRESS + XLATE_LPC(poff)

lpc_pad_params:
	.long	PAD_MMIO_ADDR(LPC_CLKOUT0)
	.long	0x44000400
	.long	0x0003C000
	.long	PAD_MMIO_ADDR(LPC_AD0)
	.long	0x44000402
	.long	0x0003F000
	.long	PAD_MMIO_ADDR(LPC_AD1)
	.long	0x44000402
	.long	0x0003F000
	.long	PAD_MMIO_ADDR(LPC_AD2)
	.long	0x44000402
	.long	0x0003F000
	.long	PAD_MMIO_ADDR(LPC_AD3)
	.long	0x44000402
	.long	0x0003F000
	.long	PAD_MMIO_ADDR(LPC_FRAME)
	.long	0x44000400
	.long	0x0003F000
	.long	PAD_MMIO_ADDR(LPC_CLKOUT1)
	.long	0x44000400
	.long	0x0003C000
num_lpc_pads = ( . - lpc_pad_params) / 0xc
