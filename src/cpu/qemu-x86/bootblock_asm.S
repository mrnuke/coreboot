/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015  Alexandru Gagniuc <mr.nuke.me@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include <console/post_codes.h>

#define STACK_SIZE 0x10000
#define STACK_BASE 0xd0000

.intel_syntax noprefix

#define post_code(code) \
	mov	eax, code; \
	out	0x80, eax

.global bootblock_pre_c_entry

.section .text
bootblock_pre_c_entry:

	/* Set up a stack */
	mov	esp, (STACK_BASE + STACK_SIZE)

	/* Clear .car.global section */
	mov	ecx, _car_global_end
	mov	edi, _car_global_start
	sub	ecx, edi
	shr	ecx, 2
	xor	eax, eax
	rep	stos dword ptr es:[edi], eax

	/*
	 * We have the following values saved from earlier:
	 * mm0: BIST result
	 * mm1: TSC timestamp low 32 bits
	 * mm2: TSC timestamp high 32 bits
	 */
	movd	eax, mm2
	push	eax
	movd	eax, mm1
	push	eax
	movd	eax, mm0
	push	eax
	call	bootblock_main

.halt_forever:
	post_code(POST_DEAD_CODE)
	hlt
	jmp	.halt_forever
