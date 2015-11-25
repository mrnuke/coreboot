/*
 * This file is part of the libpayload project.
 *
 * Copyright (C) 2008 Advanced Micro Devices, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * @file x86/timer.c
 * x86 specific timer routines
 */

#include <libpayload.h>
#include <arch/cpuid.h>
#include <arch/rdtsc.h>
#include <arch/msr.h>

#define MSR_PLATFORM_INFO	0xce
/**
 * @ingroup arch
 * Global variable containing the speed of the processor in KHz.
 */
uint32_t cpu_khz;

const char intel_cpuid_mfg_string[] = "GenuineIntel";

/*
 * Certain Atom SOCs don't either don't have an 8254 timer (PIT), or coreboot
 * disables the PIT. In these cases TSC calibration by PIT will hang.
 *
 * NOTE: This table and its associated helper functions can be extended to
 * support a larger range of CPUs and access methods. This only includes tested
 * CPUs.
 */
static const struct fsb_freq_descriptor {
	uint8_t cpu_family;
	uint8_t cpu_model;
	unsigned int base_clock_khz;
} intel_freq_table[] = {
	{ 6, 0x5c, 100000 },
};

static const struct fsb_freq_descriptor *get_cpu_freq_info(void)
{
	size_t i;
	struct cpuid_fms fms = cpuid_get_fms();

	for (i = 0; i < ARRAY_SIZE(intel_freq_table); i++) {
		if ((intel_freq_table[i].cpu_family == fms.family) &&
		    (intel_freq_table[i].cpu_model == fms.model)) {
			return &intel_freq_table[i];
		}
	}

	return NULL;
}

static int is_intel_cpu(void)
{
	char id_string[12];
	struct cpuid_result res;

	/* Get manufacturer's ID string */
	res = cpuid(0);
	memcpy(id_string + 0, &res.ebx, 4);
	memcpy(id_string + 4, &res.edx, 4);
	memcpy(id_string + 8, &res.ecx, 4);

	return !memcmp(intel_cpuid_mfg_string, id_string, 12);
}

/*
 * Get the speed of the processor's timestamp counter on supported CPUs
 */
static unsigned int get_cpu_speed_by_const_tsc(void)
{
	uint64_t msr;
	uint32_t tsc_multiplier;
	const struct fsb_freq_descriptor *freq_info;

	if (!is_intel_cpu())
		return 0;

	freq_info = get_cpu_freq_info();
	if (!freq_info)
		return 0;

	msr = _rdmsr(MSR_PLATFORM_INFO);
	tsc_multiplier = (msr >> 8) & 0xff;

	cpu_khz =  (freq_info->base_clock_khz * tsc_multiplier);
	return cpu_khz;
}

/*
 * Get the speed of the processor's timestamp counter by calibrating it
 * against the 8254 programmable interval timer.
 * This function waits 2 ms to get an accurate calibration.
 */
static unsigned int get_cpu_speed_by_8254_timer(void)
{
	unsigned long long start, end;
	const uint32_t clock_rate = 1193182; // 1.193182 MHz
	const uint16_t interval = (2 * clock_rate) / 1000; // 2 ms

	/* Set up the PPC port - disable the speaker, enable the T2 gate. */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/* Set the PIT to Mode 0, counter 2, word access. */
	outb(0xB0, 0x43);

	/* Load the interval into the counter. */
	outb(interval & 0xff, 0x42);
	outb((interval >> 8) & 0xff, 0x42);

	/* Read the number of ticks during the period. */
	start = rdtsc();
	while (!(inb(0x61) & 0x20)) ;
	end = rdtsc();

	/*
	 * The number of milliseconds for a period is
	 * clock_rate / (interval * 1000). Multiply that by the number of
	 * measured clocks to get the kHz value.
	 */
	cpu_khz = (end - start) * clock_rate / (1000 * interval);

	return cpu_khz;
}

/**
 * Calculate the speed of the processor for use in delays.
 *
 * @return The CPU speed in kHz.
 */
unsigned int get_cpu_speed(void)
{
	uint32_t tsc_rate_khz;

	tsc_rate_khz = get_cpu_speed_by_const_tsc();
	if (tsc_rate_khz)
		return tsc_rate_khz;

	tsc_rate_khz = get_cpu_speed_by_8254_timer();

	return tsc_rate_khz;
}
