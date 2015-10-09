ifeq ($(CONFIG_SOC_INTEL_APOLLOLAKE),y)

subdirs-y += ../../../cpu/intel/microcode
subdirs-y += ../../../cpu/intel/turbo
subdirs-y += ../../../cpu/x86/lapic
subdirs-y += ../../../cpu/x86/mtrr
subdirs-y += ../../../cpu/x86/smm
subdirs-y += ../../../cpu/x86/tsc

bootblock-y += bootblock/bootblock_car.c
bootblock-y += cpu.c
bootblock-y += gpio.c
bootblock-y += bootblock/cache_as_ram.S
bootblock-y += bootblock/early_chipset_config.S

romstage-y += cpu.c
romstage-y += gpio.c

ramstage-y += cpu.c
ramstage-y += gpio.c

romstage-y += placeholders.c
smm-y += placeholders.c
ramstage-y += placeholders.c

# cpu_microcode_bins += ???

CPPFLAGS_common += -I$(src)/soc/intel/apollolake/include

endif
