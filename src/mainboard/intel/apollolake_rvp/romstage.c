/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Lance Zhao <lijian.zhao@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <soc/romstage.h>
#include <string.h>
#include <fsp/api.h>

static const uint8_t swizzling_rvp1[] = {
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

static const uint8_t swizzling0_rvp2[] = {
	23, 21, 16, 17, 18, 19, 22, 20,  3,  5,  2,  4,  7,  0,  6,  1,
	24, 27, 26, 30, 28, 25, 29, 31, 13,  8, 12, 15, 10, 14, 11,  9,
};

static const uint8_t swizzling1_rvp2[] = {
	10, 14, 12, 13,  9, 11, 15,  8,  1,  6,  2,  5,  0,  7,  3,  4,
	21, 18, 19, 22, 20, 17, 16, 23, 29, 28, 24, 27, 31, 30, 26, 25,
};

static const uint8_t swizzling2_rvp2[] = {
	13, 15, 10, 14,  9, 12,  8, 11, 22, 19, 16, 23, 21, 17, 20, 18,
	26, 24, 28, 29, 31, 30, 27, 25,  4,  5,  1,  0,  3,  6,  7,  2,
};

static const uint8_t swizzling3_rvp2[] = {
	 0,  3,  6,  7,  4,  5,  1,  2, 20, 17, 21, 16, 23, 18, 22, 19,
	15,  9, 11, 14, 12,  8, 13, 10, 26, 29, 24, 31, 25, 30, 27, 28,
};

static void rvp1_fill_memory_params(struct DRAM_CONFIG *cfg)
{
	cfg->Profile = 33;
	cfg->DIMM0SPDAddress = 0xa0;
	cfg->DIMM1SPDAddress = 0xa4;
	cfg->Ch0_RankEnable = 0;
	cfg->Ch0_DeviceWidth = 0;
	cfg->Ch0_DramDensity = 0;
	cfg->Ch0_Option = 3;
	cfg->Ch1_RankEnable = 0;
	cfg->Ch1_DeviceWidth = 0;
	cfg->Ch1_DramDensity = 0;
	cfg->Ch1_Option = 3;
	cfg->Ch2_RankEnable = 0;
	cfg->Ch2_DeviceWidth = 0;
	cfg->Ch2_DramDensity = 0;
	cfg->Ch2_Option = 3;
	cfg->Ch3_RankEnable = 0;
	cfg->Ch3_DeviceWidth = 0;
	cfg->Ch3_DramDensity = 0;
	cfg->Ch3_Option = 3;
	memcpy(cfg->Ch0_Bit_swizzling, swizzling_rvp1, sizeof(swizzling_rvp1));
	memcpy(cfg->Ch1_Bit_swizzling, swizzling_rvp1, sizeof(swizzling_rvp1));
	memcpy(cfg->Ch2_Bit_swizzling, swizzling_rvp1, sizeof(swizzling_rvp1));
	memcpy(cfg->Ch3_Bit_swizzling, swizzling_rvp1, sizeof(swizzling_rvp1));
}

static void rvp2_fill_memory_params(struct DRAM_CONFIG *cfg)
{
	cfg->Profile = 5;
	cfg->DIMM0SPDAddress = 0;
	cfg->DIMM1SPDAddress = 0;
	cfg->Ch0_RankEnable = 3;
	cfg->Ch0_DeviceWidth = 2;
	cfg->Ch0_DramDensity = 0;
	cfg->Ch0_Option = 3;
	cfg->Ch1_RankEnable = 3;
	cfg->Ch1_DeviceWidth = 2;
	cfg->Ch1_DramDensity = 0;
	cfg->Ch1_Option = 3;
	cfg->Ch2_RankEnable = 3;
	cfg->Ch2_DeviceWidth = 2;
	cfg->Ch2_DramDensity = 0;
	cfg->Ch2_Option = 3;
	cfg->Ch3_RankEnable = 3;
	cfg->Ch3_DeviceWidth = 2;
	cfg->Ch3_DramDensity = 0;
	cfg->Ch3_Option = 3;
	memcpy(cfg->Ch0_Bit_swizzling, swizzling0_rvp2,
	       sizeof(swizzling0_rvp2));
	memcpy(cfg->Ch1_Bit_swizzling, swizzling1_rvp2,
	       sizeof(swizzling1_rvp2));
	memcpy(cfg->Ch2_Bit_swizzling, swizzling2_rvp2,
	       sizeof(swizzling2_rvp2));
	memcpy(cfg->Ch3_Bit_swizzling, swizzling3_rvp2,
	       sizeof(swizzling3_rvp2));
}

void mainboard_memory_init_params(struct MEMORY_INIT_UPD *memupd)
{
	struct DRAM_CONFIG *cfg = &memupd->DramConfig;

	cfg->Package = 0;
	cfg->MemoryDown = 1;
	cfg->DDR3LPageSize = 0;
	cfg->DDR3LASR = 0;
	cfg->ScramblerSupport = 1;
	cfg->ChannelHashMask = 0;
	cfg->SliceHashMask = 0;
	cfg->InterleavedMode = 0;
	cfg->ChannelsSlicesEnable = 0;
	cfg->MinRefRate2xEnable = 0;
	cfg->DualRankSupportEnable = 1;
	cfg->DisableFastBoot = 0;
	cfg->RmtMode = 0;
	cfg->MemorySizeLimit = 0;
	cfg->LowMemoryMaxValue = 0;
	cfg->HighMemoryMaxValue = 0;
	cfg->DramReserved = 0;

	if (IS_ENABLED(CONFIG_BOARD_INTEL_APOLLOLAKE_RVP1))
		rvp1_fill_memory_params(cfg);
	else
		rvp2_fill_memory_params(cfg);
}
