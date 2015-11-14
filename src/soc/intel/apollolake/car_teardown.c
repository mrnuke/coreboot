/*
 * Cache-as-ram teardown for apollolake SOC. See detailed explanation below.
 *
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

#include <bootstate.h>
#include <console/console.h>
#include <cpu/cpu.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/tsc.h>
#include <cbmem.h>
#include <symbols.h>

#define EVICT_CTL_MSR		0x2e0

/*
 * The CAR teardown on apollolake is more complicated than the standard x86
 * teardown paths because romstage executes in CAR. That means romstage cannot
 * do the teardown. For performance reasons, the cache is also used as a backing
 * store for RAM after raminit.
 *
 * This results in a cache with both a CAR region, and memory-backed regions:
 *   - Invalidating the entire cache will evict stack and code that has not yet
 *     been commited, to RAM, resulting in a crash.
 *   - A 'wbinvd' will result in a crash during the write-back phase because
 *     the CAR region has no backing store.
 *
 * This teardown path resolves these problems by first flushing important data
 * out of cache, to memory. After this operation, it is safe to invalidate the
 * entire cache, which is then followed by standard MTRR housekeeping.
 *
 * For performance reasons, only the memory regions which may have been written
 * to are flushed. This includes ramstage code and cbmem. A complete flush of
 * all RAM ranges would take several seconds.
 */

struct mem_region {
	uintptr_t start;
	uintptr_t end;
};

/* Returns true if two memory regions overlap, or one contains the other */
static bool mem_regions_overlap(const struct mem_region *a,
				const struct mem_region *b)
{
	if ((a->end < b->start) || (b->end < a->start))
		return false;

	return true;
}

/* Merge two regions into one. Assumes regions overlap */
static void merge_regions(struct mem_region *a, struct mem_region *b)
{
	/* Merge second region into first */
	a->start = MIN(a->start, b->start);
	a->end = MAX(a->end, b->end);

	/* Disable the second region */
	b->start = b->end = 0;
}

static void clflush(uintptr_t addr)
{
	__asm__ volatile ("clflush (%0)"::"r" (addr));
}

static void clflush_mem_range(uintptr_t start, uintptr_t end)
{
	end = ALIGN_UP(end, 64);

	for (start = ALIGN_DOWN(start, 64); start < end; start += 64)
		clflush(start);
}

static void flush_ram_cache_and_invalidate(void)
{
	size_t cbmem_size;
	struct mem_region ramstage, cbmem;

	/* Figure out where ramstage and cbmem reside */
	ramstage.start = (uintptr_t)&_program;
	ramstage.end = (uintptr_t)&_eprogram;

	cbmem_region_used(&cbmem.start, &cbmem_size);
	cbmem.end = cbmem.start + cbmem_size;

	if (mem_regions_overlap(&cbmem, &ramstage))
		merge_regions(&cbmem, &ramstage);

	/* TODO: Carve FSP reserved mem region out of flushable ranges */

	/* Flush ramstage code and stack */
	clflush_mem_range(cbmem.start, cbmem.end);
	clflush_mem_range(ramstage.start, ramstage.end);

	/* Now that important data is flushed, invalidate all caches */
	invd();
}

static void disable_car_region_and_no_evict_mode(void)
{
	msr_t msr;

	/* Disable variable and fixed MTRRs */
	msr.lo = msr.hi = 0;
	wrmsr(MTRR_DEF_TYPE_MSR, msr);
	/* Disable CAR MTRR */
	wrmsr(MTRR_PHYS_BASE(0), msr);
	wrmsr(MTRR_PHYS_MASK(0), msr);

	/* Switch out of "no evict" mode */
	msr = rdmsr(EVICT_CTL_MSR);
	msr.lo &= ~2;
	wrmsr(EVICT_CTL_MSR, msr);

	msr.lo &= ~1;
	wrmsr(EVICT_CTL_MSR, msr);

	/* Re-enable remaining MSRs */
	msr.lo = MTRR_DEF_TYPE_EN;
	msr.hi = 0;
	wrmsr(MTRR_DEF_TYPE_MSR, msr);
}

static void tear_down_car(void *unused_arg)
{
	(void) unused_arg;

	flush_ram_cache_and_invalidate();
	disable_car_region_and_no_evict_mode();
}

BOOT_STATE_INIT_ENTRY(BS_PRE_DEVICE, BS_ON_ENTRY, tear_down_car, NULL);
