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

#include <device/pci_def.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/post_code.h>
#include <cbmem.h>

#define CR0_CACHE_DISABLE	(1 << 30)
#define CR0_NO_WRITE		(1 << 29)

#define EVICT_CTL_MSR		0x2e0

.intel_syntax noprefix

#undef post_code
#define post_code(value)	\
	mov	al, value;	\
	outb	CONFIG_POST_IO_PORT, al

.global cache_as_ram
cache_as_ram:
	post_code(0x21)

	/* Clear/disable fixed MTRRs */
	mov	ebx, offset fixed_mtrr_list_size
	xor	eax, eax
	xor	edx, edx
clear_fixed_mtrr:
	add	ebx, -2
	movzxw	ecx, word ptr [fixed_mtrr_list + ebx]
	wrmsr
	jnz	clear_fixed_mtrr

	post_code(0x22)

	/* Figure put how many MTRRs we have, and clear them out */
	mov	ecx, MTRR_CAP_MSR
	rdmsr
	movzxb	ebx, al		/* Number of variable MTRRs */
	mov	ecx, MTRR_PHYS_BASE(0)
	xor	eax, eax
	xor	edx, edx
clear_var_mtrr:
	wrmsr
	inc	ecx
	wrmsr
	inc	ecx
	dec	ebx
	jnz	clear_var_mtrr

	post_code(0x23)

	/* Configure default memory type to uncacheable (UC) */
	mov 	ecx, MTRR_DEF_TYPE_MSR
	rdmsr
	and	eax, ~0xcff
	wrmsr

	post_code(0x24)

	/* Configure CAR region as write-back (WB) */
	mov	ecx, MTRR_PHYS_BASE(0)
	mov	eax, CONFIG_DCACHE_RAM_BASE		/* base */
	or	eax, MTRR_TYPE_WRBACK
	xor	edx, edx
	wrmsr

	/* Configure the MTRR mask for the size region */
	mov	ecx, MTRR_PHYS_MASK(0)
	mov	eax, ~(CONFIG_DCACHE_RAM_SIZE - 1)	/* size mask */
	or	eax, MTRR_PHYS_MASK_VALID
	wrmsr

	post_code(0x25)

	/* Enable variable MTRRs */
	mov	ecx, MTRR_DEF_TYPE_MSR
	rdmsr
	or	eax, MTRR_DEF_TYPE_EN
	wrmsr

	/* Cache tricks */
	mov	eax, cr0
	and	eax, ~(CR0_CACHE_DISABLE | CR0_NO_WRITE)
	invd
	mov	cr0, eax

	/* Disable cache eviction (setup stage) */
	mov	ecx, EVICT_CTL_MSR
	rdmsr
	or	eax, 1
	wrmsr

	post_code(0x26)

	/* Write something to each cache line */
	mov	eax, 0xcafebabe
	mov	edi, CONFIG_DCACHE_RAM_BASE
	mov	ecx, (0x80000 >> 6)
cache_init_loop:
	mov	[edi], eax
	sfence
	add	edi, 64
	loop cache_init_loop

	post_code(0x27)

	/* Disable cache eviction (run stage) */
	mov	ecx, EVICT_CTL_MSR
	rdmsr
	or	eax, 2
	wrmsr

	post_code(0x28)

car_init_done:

	/* Setup bootblock stack */
	mov	esp, CONFIG_DCACHE_RAM_BASE
	add 	esp, CONFIG_DCACHE_RAM_BOOTBLOCK_STACK_SIZE

	/* Make sure CAR region is executable */
	mov	ecx, 0x120
	rdmsr
	or	ah, 0x1
	wrmsr

before_carstage:
	post_code(0x2b)

	/* Call romstage.c main function. */
	push .halt_forever	/* In case bootblock_car_main returns */
	jmp bootblock_car_main

	/* Never reached */

.halt_forever:
	post_code(POST_DEAD_CODE)
	hlt
	jmp	.halt_forever

fixed_mtrr_list:
	.word	MTRR_FIX_64K_00000
	.word	MTRR_FIX_16K_80000
	.word	MTRR_FIX_16K_A0000
	.word	MTRR_FIX_4K_C0000
	.word	MTRR_FIX_4K_C8000
	.word	MTRR_FIX_4K_D0000
	.word	MTRR_FIX_4K_D8000
	.word	MTRR_FIX_4K_E0000
	.word	MTRR_FIX_4K_E8000
	.word	MTRR_FIX_4K_F0000
	.word	MTRR_FIX_4K_F8000
fixed_mtrr_list_size = . - fixed_mtrr_list
