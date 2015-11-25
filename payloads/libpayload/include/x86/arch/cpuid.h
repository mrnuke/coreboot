/*
 * This file is part of the libpayload project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
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

#ifndef _ARCH_X86_CPUID_H
#define _ARCH_X86_CPUID_H

struct cpuid_result {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
};

struct cpuid_fms {
	uint16_t family;
	uint8_t model;
	uint8_t stepping;
};

static inline struct cpuid_result cpuid(uint32_t op_eax)
{
	struct cpuid_result res;

	__asm__ volatile(
		"cpuid"
		: "=a" (res.eax), "=b" (res.ebx), "=c" (res.ecx), "=d" (res.edx)
		: "a" (op_eax)
	);

	return res;
}

static inline uint32_t cpuid_eax(uint32_t op_eax)
{
	struct cpuid_result res = cpuid(op_eax);

	return res.eax;
}

static inline uint32_t cpuid_ebx(uint32_t op_eax)
{
	struct cpuid_result res = cpuid(op_eax);

	return res.ebx;
}

static inline uint32_t cpuid_ecx(uint32_t op_eax)
{
	struct cpuid_result res = cpuid(op_eax);

	return res.ecx;
}

static inline uint32_t cpuid_edx(uint32_t op_eax)
{
	struct cpuid_result res = cpuid(op_eax);

	return res.edx;
}

/**
 * Extract the CPU family, model and stepping
 *
 * For details, see:
 * Intel 64 and IA-32 Architectures Software Developer’s Manual
 * Combined Volumes: 1, 2A, 2B, 2C, 3A, 3B, 3C and 3D
 * Order Number: 325462-056US
 * - Figure 3-6. Version Information Returned by CPUID in EAX
 *   pg. 3-190 Vol. 2A
 *
 * and
 *
 * AMD CPUID Specification
 * Publication # 25481 Revision: 2.34
 * - CPUID Fn0000_0001_EAX Family, Model, Stepping Identifiers
 *   pg. 10
 */
static inline struct cpuid_fms cpuid_get_fms(void)
{
	struct cpuid_fms fms;
	const uint32_t eax = cpuid_eax(1);

	fms.family = (eax >> 8) & 0xf;
	if (fms.family == 0xf)
		fms.family += (eax >> 20) & 0xff;

	fms.model = ((eax >> 4) & 0xf);
	if ((fms.family == 0xf) | (fms.family == 6))
		fms.model |= ((eax >> 16) & 0xf) << 4;

	fms.stepping = eax & 0xf;

	return fms;
}

#endif /* _ARCH_X86_CPUID_H */
