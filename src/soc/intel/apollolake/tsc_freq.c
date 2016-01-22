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

#include <cpu/x86/msr.h>
#include <cpu/x86/tsc.h>
#include <soc/cpu.h>

unsigned long tsc_freq_mhz(void)
{
	msr_t msr = rdmsr(MSR_PLATFORM_INFO);
	return (BASE_CLOCK_MHZ * ((msr.lo >> 8) & 0xff));
}
