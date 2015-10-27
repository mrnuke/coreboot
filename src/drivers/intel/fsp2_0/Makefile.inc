
CPPFLAGS_common += -I$(src)/drivers/intel/fsp2_0/include

cbfs-files-$(CONFIG_ADD_FSP_BINARIES) += blobs/fsp-m.bin
blobs/fsp-m.bin-file := $(call strip_quotes,$(CONFIG_FSP_M_FILE))
blobs/fsp-m.bin-type := raw

cbfs-files-$(CONFIG_ADD_FSP_BINARIES) += blobs/fsp-s.bin
blobs/fsp-s.bin-file := $(call strip_quotes,$(CONFIG_FSP_S_FILE))
blobs/fsp-s.bin-type := raw
