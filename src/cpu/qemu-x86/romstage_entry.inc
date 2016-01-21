/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2000,2007 Ronald G. Minnich <rminnich@gmail.com>
 * Copyright (C) 2007-2008 coresystems GmbH
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

#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/post_code.h>
#include <cbmem.h>

#define STACK_SIZE 0x10000
#define STACK_BASE 0xd0000

qemu_x86_assembly_entry:
	post_code(0x20)

	/* Set up the stack pointer. */
	movl	$(STACK_BASE + STACK_SIZE), %eax
	movl	%eax, %esp

	/* Clear .car.global section */
	movl	$_car_global_end, %ecx
	movl	$_car_global_start, %edi
	sub	%edi, %ecx
	shr	$2, %ecx
	xorl	%eax, %eax
	rep	stosl

before_romstage:
	post_code(0x29)
	/* Call romstage.c main function. */
	call	main

	post_code(0x30)

__main:
	post_code(POST_PREPARE_RAMSTAGE)
	cld			/* Clear direction flag. */

	movl	$CONFIG_RAMTOP, %esp
	movl	%esp, %ebp
	call	copy_and_run

.Lhlt:
	post_code(POST_DEAD_CODE)
	hlt
	jmp	.Lhlt
