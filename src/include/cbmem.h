/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2009 coresystems GmbH
 * Copyright (C) 2013 Google, Inc.
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

#ifndef _CBMEM_H_
#define _CBMEM_H_

#include <commonlib/cbmem_id.h>
#include <rules.h>

#if IS_ENABLED(CONFIG_HAVE_ACPI_RESUME) && \
	! IS_ENABLED(CONFIG_RELOCATABLE_RAMSTAGE)
#define HIGH_MEMORY_SAVE	(CONFIG_RAMTOP - CONFIG_RAMBASE)
#else
#define HIGH_MEMORY_SAVE	0
#endif

/* Delegation of resume backup memory so we don't have to
 * (slowly) handle backing up OS memory in romstage.c
 */
#define CBMEM_BOOT_MODE		0x610
#define CBMEM_RESUME_BACKUP	0x614
#define CBMEM_FSP_HOB_PTR	0x614

#ifndef __ASSEMBLER__
#include <stddef.h>
#include <stdint.h>
#include <boot/coreboot_tables.h>

struct cbmem_entry;

/*
 * The dynamic cbmem infrastructure allows for growing cbmem dynamically as
 * things are added. It requires an external function, cbmem_top(), to be
 * implemented by the board or chipset to define the upper address where
 * cbmem lives. This address is required to be a 32-bit address. Additionally,
 * the address needs to be consistent in both romstage and ramstage.  The
 * dynamic cbmem infrastructure allocates new regions below the last allocated
 * region. Regions are defined by a cbmem_entry struct that is opaque. Regions
 * may be removed, but the last one added is the only that can be removed.
 */

#define DYN_CBMEM_ALIGN_SIZE (4096)
#define CBMEM_ROOT_SIZE      DYN_CBMEM_ALIGN_SIZE

/* The root region is at least DYN_CBMEM_ALIGN_SIZE . */
#define CBMEM_ROOT_MIN_SIZE DYN_CBMEM_ALIGN_SIZE
#define CBMEM_LG_ALIGN CBMEM_ROOT_MIN_SIZE

/* Small allocation parameters. */
#define CBMEM_SM_ROOT_SIZE 1024
#define CBMEM_SM_ALIGN 32

/* Determine the size for CBMEM root and the small allocations */
static inline size_t cbmem_overhead_size(void)
{
   return 2 * CBMEM_ROOT_MIN_SIZE;
}

/* By default cbmem is attempted to be recovered. Returns 0 if cbmem was
 * recovered or 1 if cbmem had to be reinitialized. */
int cbmem_initialize(void);
int cbmem_initialize_id_size(u32 id, u64 size);

/* Initialize cbmem to be empty. */
void cbmem_initialize_empty(void);
void cbmem_initialize_empty_id_size(u32 id, u64 size);

/* Return the top address for dynamic cbmem. The address returned needs to
 * be consistent across romstage and ramstage, and it is required to be
 * below 4GiB. */
void *cbmem_top(void);

/* Add a cbmem entry of a given size and id. These return NULL on failure. The
 * add function performs a find first and do not check against the original
 * size. */
const struct cbmem_entry *cbmem_entry_add(u32 id, u64 size);

/* Find a cbmem entry of a given id. These return NULL on failure. */
const struct cbmem_entry *cbmem_entry_find(u32 id);

/* Remove a region defined by a cbmem_entry. Returns 0 on success, < 0 on
 * error. Note: A cbmem_entry cannot be removed unless it was the last one
 * added. */
int cbmem_entry_remove(const struct cbmem_entry *entry);

/* cbmem_entry accessors to get pointer and size of a cbmem_entry. */
void *cbmem_entry_start(const struct cbmem_entry *entry);
u64 cbmem_entry_size(const struct cbmem_entry *entry);

/* Returns 0 if old cbmem was recovered. Recovery is only attempted if
 * s3resume is non-zero. */
int cbmem_recovery(int s3resume);
/* Add a cbmem entry of a given size and id. These return NULL on failure. The
 * add function performs a find first and do not check against the original
 * size. */
void *cbmem_add(u32 id, u64 size);
/* Find a cbmem entry of a given id. These return NULL on failure. */
void *cbmem_find(u32 id);
/* Get location and size of CBMEM region in memory */
void cbmem_region_used(uintptr_t *base, size_t *size);

/* Indicate to each hook if cbmem is being recovered or not. */
typedef void (* const cbmem_init_hook_t)(int is_recovery);
void cbmem_run_init_hooks(int is_recovery);
void cbmem_fail_resume(void);

/* Ramstage only functions. */
/* Add the cbmem memory used to the memory map at boot. */
void cbmem_add_bootmem(void);
void cbmem_list(void);
void cbmem_add_records_to_cbtable(struct lb_header *header);

#if ENV_RAMSTAGE
#define ROMSTAGE_CBMEM_INIT_HOOK(init_fn_) static cbmem_init_hook_t \
	init_fn_ ## _unused_ __attribute__((unused)) = init_fn_;
#define RAMSTAGE_CBMEM_INIT_HOOK(init_fn_) \
	static cbmem_init_hook_t init_fn_ ## _ptr_ __attribute__((used, \
	section(".rodata.cbmem_init_hooks"))) = init_fn_;
#elif ENV_ROMSTAGE
#define ROMSTAGE_CBMEM_INIT_HOOK(init_fn_) \
	static cbmem_init_hook_t init_fn_ ## _ptr_ __attribute__((used, \
	section(".rodata.cbmem_init_hooks"))) = init_fn_;
#define RAMSTAGE_CBMEM_INIT_HOOK(init_fn_) static cbmem_init_hook_t \
	init_fn_ ## _unused_ __attribute__((unused)) = init_fn_;
#else
#define ROMSTAGE_CBMEM_INIT_HOOK(init_fn_) static cbmem_init_hook_t \
	init_fn_ ## _unused_ __attribute__((unused)) = init_fn_;
#define RAMSTAGE_CBMEM_INIT_HOOK(init_fn_) static cbmem_init_hook_t \
	init_fn_ ## _unused2_ __attribute__((unused)) = init_fn_;
#endif /* ENV_RAMSTAGE */


/* These are for compatibility with old boards only. Any new chipset and board
 * must implement cbmem_top() for both romstage and ramstage to support
 * early features like COLLECT_TIMESTAMPS and CBMEM_CONSOLE.
 */
#if IS_ENABLED(CONFIG_ARCH_X86) && IS_ENABLED(CONFIG_LATE_CBMEM_INIT)
/* Note that many of the current providers of get_top_of_ram() conditionally
 * return 0 when the sleep type is non S3. i.e. cold and warm boots would
 * return 0 from get_top_of_ram(). */
unsigned long get_top_of_ram(void);
void set_top_of_ram(uint64_t ramtop);
void backup_top_of_ram(uint64_t ramtop);
#endif

#endif /* __ASSEMBLER__ */


#endif /* _CBMEM_H_ */
