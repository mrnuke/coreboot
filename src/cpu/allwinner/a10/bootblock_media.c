/*
 * CBFS accessors for bootblock stage.
 *
 * This is how this works: The mask ROM loads our booblock to SRAM, which
 * includes the CBFS header. That's how we've set things up. Then we initialize
 * the RAM before passing control to the rest of coreboot, and thus before
 * init_default_cbfs_media() gets called. Then we get a chance to put the
 * entire CBFS as some predetermined RAM location, and further stages can
 * simply
 *
 * Copyright (C) 2013  Alexandru Gagniuc <mr.nuke.me@gmail.com>
 * Subject to the GNU GPL v2, or (at your option) any later version.
 */

#include "ram_segs.h"

#include <cbfs.h>
#include <config.h>
#include <console/console.h>
#include <string.h>
#include <cpu/allwinner/a10/mmc.h>
#include <lib.h>
#include <cbmem.h>

#if IS_ENABLED(CONFIG_ALLWINNER_DEBUG_MMC)
#define TRACE(x...) printk(BIOS_DEBUG, "[boot media] " x)
#else
#define TRACE(x...)
#endif

struct cbfs_mmc_context {
	struct mmc *mmc;
	void *cbfs_base;
};

static int dummy_open(struct cbfs_media *media)
{
	TRACE("default_media->open()\n");
	return 0;
}

static int dummy_close(struct cbfs_media *media)
{
	TRACE("default_media->close()\n");
	return 0;
}

static void *on_chip_memory_map(struct cbfs_media *media, size_t offset,
				 size_t count)
{
	TRACE("default_media->map(0x%x, 0x%x)\n", offset, count);
	struct cbfs_mmc_context *ctx = (void *)media->context;

	return ctx->cbfs_base + offset;
}

static void * dummy_unmap(struct cbfs_media *media, const void *address)
{
	return NULL;
}

static size_t mmc_card_read(struct cbfs_media *media, void *dest,
			  size_t offset, size_t count)
{
	struct cbfs_mmc_context *ctx = (void *)media->context;

	memcpy(dest, ctx->cbfs_base + offset, count);

	return count;
}

/*
 * This function does some things in a less than stellar way. It is a hack on
 * top of other hacks.
 * The reason for calling sunxi_mmc_init(), and then the generic mmc_init() is
 * that sunxi_mmc_init() gives us a mmc device pointer based on the MMC
 * controller number. That's also a hack, as we (for now) always select MMC 0.
 * That needs to be fixed.
 * The generic MMC layer intentionally does not define a way to create and store
 * the mmc structs in order to avoid needing a global list of mmc structs.
 */
int init_default_cbfs_media(struct cbfs_media *media)
{
	/* It's OK to have a static context. We're in the bootblock. */
	static struct cbfs_mmc_context context;
	static bool default_media_was_init = false;

	/* The CBFS header was loaded to RAM by the mask ROM */
	struct cbfs_header *header = (void *)CONFIG_BOOTBLOCK_BASE +
					     CONFIG_CBFS_HEADER_ROM_OFFSET;


	if (default_media_was_init)
		printk(BIOS_WARNING, "%s called more then once\n", __func__);

	if (CBFS_HEADER_MAGIC != ntohl(header->magic)) {
		printk(BIOS_ERR, "Invalid CBFS master header at %p\n", header);
		/* Try to continue. Maybe we can get a good header from MMC */
	}

	static struct mmc *mmc;

	media->open = dummy_open;
	media->close = dummy_close;
	media->map = on_chip_memory_map;
	media->unmap = dummy_unmap;
	media->read = mmc_card_read;

	size_t rdr;
	size_t bs = 512;
	size_t start_block = (8 << 10) / bs;
	size_t n_blocks = CEIL_DIV(CONFIG_ROM_SIZE + 32, bs);
	void * dest = a1x_get_cbfs_cache_top() - n_blocks * bs;
	media->context = (void *)&context;
	context.cbfs_base = dest + 32;

	header = (void *)context.cbfs_base + CONFIG_CBFS_HEADER_ROM_OFFSET;
	if (CBFS_HEADER_MAGIC == ntohl(header->magic)) {
		printk(BIOS_ERR, "Already have CBFS master header at %p\n", header);
		return 0;
	}
	printk(BIOS_ERR, "No valid CBFS master header at %p\n", header);

	/* This sequence is a little confusing. See function description */
	TRACE("Calling sunxi MMC init\n");
	sunxi_mmc_init(0, &mmc);
	context.mmc = mmc;
	TRACE("Calling generic MMC init\n");
	mmc_init(mmc);

	TRACE("Copying coreboot.rom to RAM\n");
	rdr = context.mmc->block_dev.block_read(&context.mmc->block_dev,
						start_block, n_blocks, dest);
	if (rdr < n_blocks)
		printk(BIOS_CRIT, "Failed read full CBFS. Expect problems\n");

	media->context = (void*)&context;

	default_media_was_init = true;
	return 0;
}
