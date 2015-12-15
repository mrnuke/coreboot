
romstage-y += hand_off_block.c
romstage-y += util.c
romstage-y += memory_init.c

ramstage-y += graphics.c
ramstage-y += hand_off_block.c
ramstage-y += notify.c
ramstage-y += silicon_init.c
ramstage-y += util.c

CPPFLAGS_common += -I$(src)/drivers/intel/fsp2_0/include

cbfs-files-$(CONFIG_ADD_FSP_BINARIES) += blobs/fsp-m.bin
blobs/fsp-m.bin-file := $(call strip_quotes,$(CONFIG_FSP_M_FILE))
blobs/fsp-m.bin-type := raw

cbfs-files-$(CONFIG_ADD_FSP_BINARIES) += blobs/fsp-s.bin
blobs/fsp-s.bin-file := $(call strip_quotes,$(CONFIG_FSP_S_FILE))
blobs/fsp-s.bin-type := raw

cbfs-files-$(CONFIG_ADD_VBT_DATA_FILE) += vbt.bin
vbt.bin-file := $(call strip_quotes,$(CONFIG_VBT_FILE))
vbt.bin-type := raw
