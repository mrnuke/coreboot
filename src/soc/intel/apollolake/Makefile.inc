ifeq ($(CONFIG_SOC_INTEL_APOLLOLAKE),y)

subdirs-y += ../../../cpu/intel/microcode
subdirs-y += ../../../cpu/intel/turbo
subdirs-y += ../../../cpu/x86/cache
subdirs-y += ../../../cpu/x86/lapic
subdirs-y += ../../../cpu/x86/mtrr
subdirs-y += ../../../cpu/x86/smm
subdirs-y += ../../../cpu/x86/tsc

bootblock-y += bootblock/bootblock_car.c
bootblock-y += gpio.c
bootblock-y += bootblock/cache_as_ram.S
bootblock-y += bootblock/early_chipset_config.S
bootblock-y += mmap_boot.c
bootblock-y += tsc_freq.c
bootblock-y += uart_early.c

cpu_incs-y += $(src)/soc/intel/apollolake/romstage/entry.inc
romstage-y += gpio.c
romstage-y += memmap.c
romstage-y += mmap_boot.c
romstage-y += romstage/romstage.c
romstage-y += tsc_freq.c
romstage-y += uart_early.c

ramstage-$(CONFIG_HAVE_ACPI_TABLES) += acpi.c
ramstage-y += car_teardown.c
ramstage-y += chip.c
ramstage-y += cpu.c
ramstage-y += gpio.c
ramstage-y += graphics.c
ramstage-y += lpc.c
ramstage-y += memmap.c
ramstage-y += mmap_boot.c
ramstage-y += northbridge.c
ramstage-y += tsc_freq.c
ramstage-y += uart.c

romstage-y += placeholders.c
smm-y += placeholders.c
ramstage-y += placeholders.c

cpu_microcode_bins += /dev/null

CPPFLAGS_common += -I$(src)/soc/intel/apollolake/include

ifeq ($(CONFIG_USE_BLOBS),y)

BLOB_DIR := 3rdparty/blobs/mainboard/$(CONFIG_MAINBOARD_DIR)
SPI_FILE := $(call strip_quotes,$(BLOB_DIR)/$(CONFIG_PREBUILT_SPI_IMAGE))

$(obj)/coreboot.pre: $(objcbfs)/romstage.elf $(obj)/coreboot.pre1 $(CBFSTOOL) \
		     $(objcbfs)/bootblock.bin $(objcbfs)/romstage.elf
	@cp $(SPI_FILE) $@
	@echo injecting bootblock
	@$(CBFSTOOL) $@ write -r IBBL -f $(objcbfs)/bootblock.bin -d
	@printf "    CBFS       $(CONFIG_CBFS_PREFIX)/romstage\n"
	@$(CBFSTOOL) $@ add-stage -f $(objcbfs)/romstage.elf \
		-n $(CONFIG_CBFS_PREFIX)/romstage
endif

endif
