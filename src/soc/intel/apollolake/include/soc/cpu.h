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

#ifndef _SOC_APOLLOLAKE_CPU_H_
#define _SOC_APOLLOLAKE_CPU_H_

#include <cpu/x86/msr.h>

#define MSR_PLATFORM_INFO	0xce

#define BASE_CLOCK_MHZ		100

/*
 * Remark the cache as executable. This works around a silicon bug where
 * updating a cache line makes it non-executable.
 */
static inline void bxt_remark_cache_exec(void)
{
	msr_t msr = rdmsr(0x120);
	msr.lo |= (1 << 8);
	wrmsr(0x120, msr);
}

#endif /* _SOC_APOLLOLAKE_CPU_H_ */
