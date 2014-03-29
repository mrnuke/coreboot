#*****************************************************************************
#
# Copyright (c) 2012, Advanced Micro Devices, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Advanced Micro Devices, Inc. nor the names of
#       its contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#*****************************************************************************

# AGESA V5 Files
AGESA_ROOT = src/vendorcode/amd/agesa/f15tn

AGESA_PUB_INC =  -Isrc/mainboard/$(MAINBOARDDIR)
AGESA_PUB_INC += -I$(AGESA_ROOT)
AGESA_PUB_INC += -I$(AGESA_ROOT)/Include
AGESA_INC += -I$(AGESA_ROOT)/Lib
AGESA_INC += -I$(AGESA_ROOT)/Legacy
AGESA_INC += -I$(AGESA_ROOT)/Proc/Common
AGESA_INC += -I$(AGESA_ROOT)/Proc/HT
AGESA_INC += -I$(AGESA_ROOT)/Proc/CPU
AGESA_INC += -I$(AGESA_ROOT)/Proc/CPU/Feature
AGESA_INC += -I$(AGESA_ROOT)/Proc/CPU/Family
AGESA_INC += -I$(AGESA_ROOT)/Proc/CPU/Family/0x15
AGESA_INC += -I$(AGESA_ROOT)/Proc/CPU/Family/0x15/TN
AGESA_INC += -I$(AGESA_ROOT)/Proc/Mem
AGESA_INC += -I$(AGESA_ROOT)/Proc/Mem/NB/TN
AGESA_INC += -I$(AGESA_ROOT)/Proc/IDS
AGESA_INC += -I$(AGESA_ROOT)/Proc/IDS/Family
AGESA_INC += -I$(AGESA_ROOT)/Proc/IDS/Family/0x15
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Common
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Nb
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Nb/Family
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Nb/Family/0x15
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Nb/Feature
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/PCIe
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/PCIe/Family
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/PCIe/Family/0x15
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/PCIe/Feature
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Gfx
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Gfx/Family
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxConfig
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieConfig
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxInitLibV1
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbNbInitLibV1
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbSbLib
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieTrainingV1
AGESA_INC += -I$(AGESA_ROOT)/Proc/IDS/Family/0x15/TN
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib
AGESA_INC += -I$(AGESA_ROOT)/Proc/HT/NbCommon
AGESA_INC += -I$(AGESA_ROOT)/Proc/Mem/Main
AGESA_INC += -I$(AGESA_ROOT)/Proc/IDS/Library
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbNbInitLibV4
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbIommuIvrs
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbIvrsLib
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbSbIommuLib
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbTable
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV4
AGESA_INC += -I$(AGESA_ROOT)/Proc/Fch
AGESA_INC += -I$(AGESA_ROOT)/Proc/Fch/Common
AGESA_INC += -I$(AGESA_ROOT)/Proc/IDS/Debug
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieAspm
AGESA_INC += -I$(AGESA_ROOT)/Proc/GNB/Include/Library

AGESA_INC += -I$(src)/southbridge/amd/agesa/hudson

AGESA_CFLAGS =-march=k8-sse3 -mtune=k8-sse3 -fno-zero-initialized-in-bss -fno-strict-aliasing

export AGESA_ROOT := $(AGESA_ROOT)
export AGESA_INC  := $(AGESA_INC)
export AGESA_CFLAGS  := $(AGESA_CFLAGS)
CC := $(CC) $(AGESA_PUB_INC)
#CC := $(CC) $(AGESA_INC) $(AGESA_CFLAGS)
#######################################################################

libagesa_srcs =
libagesa_srcs += $(AGESA_ROOT)/Legacy/Proc/Dispatcher.c
libagesa_srcs += $(AGESA_ROOT)/Legacy/Proc/agesaCallouts.c
libagesa_srcs += $(AGESA_ROOT)/Legacy/Proc/hobTransfer.c
libagesa_srcs += $(AGESA_ROOT)/Lib/amdlib.c
libagesa_srcs += $(AGESA_ROOT)/Lib/helper.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnC6State.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnCpb.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnEquivalenceTable.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnInitEarlyTable.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnIoCstate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnLogicalIdTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnMicrocodePatch0600110F_Enc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnMicrocodePatchTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnMsrTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnPciTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnPowerMgmtSystemTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnPowerPlane.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnSharedMsrTable.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/F15TnUtilities.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnCacheFlushOnHalt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnCoreAfterReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnDmi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnHtc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnNbAfterReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnPowerCheck.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnPsi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/TN/cpuF15TnPstate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuCommonF15Utilities.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15BrandId.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15CacheDefaults.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15Dmi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15MmioMap.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15MsrTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15PciTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15PowerCheck.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15Utilities.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Family/0x15/cpuF15WheaInitDataTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/PreserveMailbox.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuC6State.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuCacheFlushOnHalt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuCacheInit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuCoreLeveling.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuCpb.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuDmi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuFeatureLeveling.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuFeatures.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuHtc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuHwC1e.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuIoCstate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuPsi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuPstateGather.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuPstateLeveling.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuPstateTables.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuSlit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuSrat.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Feature/cpuWhea.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/S3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/Table.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cahalt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cahaltasm.S
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuApicUtilities.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuBist.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuBrandId.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuEarlyInit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuEventLog.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuFamilyTranslation.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuGeneralServices.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuInitEarlyTable.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuLateInit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuMicrocodePatch.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuPostInit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuPowerMgmt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuPowerMgmtMultiSocket.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuPowerMgmtSingleSocket.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/cpuWarmReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/CPU/heapManager.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitEarly.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitPost.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdInitResume.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdLateRunApTask.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdS3LateRestore.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/AmdS3Save.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/CommonInits.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/CommonReturns.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/CreateStruct.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/S3RestoreState.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Common/S3SaveState.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Common/GnbLibFeatures.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtEarly.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtPost.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/GnbInitAtS3Save.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Library/GnbTimerLibWrap0/GnbTimerLibWrap0.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLibCpuAcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLibHeap.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLibIoAcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLibMemAcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLibPci.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbCommonLib/GnbLibPciAcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbFamTranslation/GnbPcieTranslation.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbFamTranslation/GnbTranslation.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxConfig/GfxConfigEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxConfig/GfxConfigLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxConfig/GfxConfigMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxConfig/GfxConfigPost.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxInitLibV1/GfxCardInfo.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxInitLibV1/GfxEnumConnectors.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxInitLibV1/GfxPowerPlayTable.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbGfxInitLibV1/GnbGfxInitLibV1.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxEnvInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxGmcInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxIntegratedInfoTableTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxLibTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxMidInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxPostInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GfxTablesTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbBapmCoeffCalcTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbEarlyInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbEnvInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbFuseTableTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbIommuIvrsTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbMidInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbPostInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbRegisterAccTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/GnbTablesTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieAlibTNFM2.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieAlibTNFS1.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieComplexDataTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieConfigTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieEarlyInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieEnvInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieLibTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieMidInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PciePostInitTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PciePowerGateTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbInitTN/PcieTablesTN.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbIommuIvrs/GnbIommuIvrs.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbIvrsLib/GnbIvrsLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbMSocketLib/GnbMSocketLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbNbInitLibV1/GnbNbInitLibV1.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbNbInitLibV4/GnbNbInitLibV4.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieAlibV1/PcieAlib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieAspm/PcieAspm.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieClkPm/PcieClkPm.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieConfig/GnbHandleLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieConfig/PcieConfigData.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieConfig/PcieConfigLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieConfig/PcieInputParser.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieConfig/PcieMapTopology.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieAspmBlackList.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieAspmExitLatency.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PciePhyServices.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PciePifServices.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PciePortRegAcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PciePortServices.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PciePowerMgmt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieSiliconServices.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieTimer.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieTopologyServices.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieUtilityLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV1/PcieWrapperRegAcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV4/PcieMaxPayloadV4.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV4/PciePortServicesV4.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV4/PciePowerMgmtV4.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieInitLibV4/PcieWrapperServicesV4.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieTrainingV1/PcieTraining.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbPcieTrainingV1/PcieWorkarounds.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbSbIommuLib/GnbSbIommuLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbSbLib/GnbSbLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbSbLib/GnbSbPcie.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbSview/GnbSview.c
libagesa_srcs += $(AGESA_ROOT)/Proc/GNB/Modules/GnbTable/GnbTable.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/Fam15Mod1x/htNbFam15Mod1x.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/Fam15Mod1x/htNbUtilitiesFam15Mod1x.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htFeat.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htInterface.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htInterfaceCoherent.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htInterfaceGeneral.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htInterfaceNonCoherent.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htMain.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htNb.c
libagesa_srcs += $(AGESA_ROOT)/Proc/HT/htNotify.c
libagesa_srcs += $(AGESA_ROOT)/Proc/IDS/Debug/IdsDebug.c
libagesa_srcs += $(AGESA_ROOT)/Proc/IDS/Debug/IdsDebugPrint.c
libagesa_srcs += $(AGESA_ROOT)/Proc/IDS/Debug/IdsDpSerial.c
libagesa_srcs += $(AGESA_ROOT)/Proc/IDS/Family/0x15/TN/IdsF15TnAllService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/IDS/Library/IdsLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ardk/ma.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/CHINTLV/mfchi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/CSINTLV/mfcsi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/DMI/mfDMI.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/ECC/mfecc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/ECC/mfemp.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/EXCLUDIMM/mfdimmexclud.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/IDENDIMM/mfidendimm.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/INTLVRN/mfintlvrn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/LVDDR3/mflvddr3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/MEMCLR/mfmemclr.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/ODTHERMAL/mfodthermal.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/PARTRN/mfParallelTraining.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/PARTRN/mfStandardTraining.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/S3/mfs3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Feat/TABLE/mftds.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/TN/mmflowtn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mdef.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/merrhdl.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/minit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mm.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmConditionalPso.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmEcc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmExcludeDimm.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmLvDdr3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmMemClr.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmMemRestore.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmNodeInterleave.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmOnlineSpare.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmParallelTraining.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmStandardTraining.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmUmaAlloc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mmflow.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/mu.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Main/muc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mndcttn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mnflowtn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mnidendimmtn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mnmcttn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mnottn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mnphytn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mnregtn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mns3tn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/TN/mntn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mn.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mnS3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mndct.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mnfeat.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mnflow.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mnmct.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mnphy.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mnreg.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/NB/mntrain3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/TN/FM2/mpUtnfm2.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/TN/FP2/mpStnfp2.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/TN/FS1/mpStnfs1.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/TN/mpStn3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/TN/mpUtn3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/TN/mptn3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/mp.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/mpmaxfreq.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/mpmr0.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/mpodtpat.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/mprtt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Ps/mpsao.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mt3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mtot3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mtrci3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mtsdi3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mtspd3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mttecc3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/DDR3/mttwl3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mthdi.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mttEdgeDetect.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mttdimbt.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mttecc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mtthrc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mtthrcSeedTrain.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mttml.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mttoptsrc.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Mem/Tech/mttsrc.c

libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Azalia/AzaliaEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Azalia/AzaliaLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Azalia/AzaliaMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Azalia/AzaliaReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Common/AcpiLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Common/FchCommon.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Common/FchLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Common/FchPeLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Common/MemLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Common/PciLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Gec/Family/Hudson2/Hudson2GecEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Gec/Family/Hudson2/Hudson2GecService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Gec/GecEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Gec/GecLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Gec/GecMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Gec/GecReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/Family/Hudson2/Hudson2HwAcpiEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/Family/Hudson2/Hudson2HwAcpiLateService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/Family/Hudson2/Hudson2HwAcpiMidService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/Family/Hudson2/Hudson2SSService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/HwAcpiEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/HwAcpiLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/HwAcpiMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/HwAcpi/HwAcpiReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/Family/Hudson2/Hudson2HwmEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/Family/Hudson2/Hudson2HwmLateService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/Family/Hudson2/Hudson2HwmMidService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/HwmEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/HwmLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/HwmMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Hwm/HwmReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Ide/IdeEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Ide/IdeLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Ide/IdeMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/Family/Hudson2/Hudson2ImcService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/FchEcEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/FchEcLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/FchEcMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/FchEcReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/ImcEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/ImcLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/ImcLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/ImcMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Imc/ImcReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/Family/Hudson2/EnvDefHudson2.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/Family/Hudson2/ResetDefHudson2.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/FchInitEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/FchInitLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/FchInitMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/FchInitReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/FchInitS3.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/FchTaskLauncher.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/InitEnvDef.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Interface/InitResetDef.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Ir/IrEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Ir/IrLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Ir/IrMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcib/PcibEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcib/PcibLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcib/PcibMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcib/PcibReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/AbEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/AbLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/AbMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/AbReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2AbEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2AbResetService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2AbService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2GppResetService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2GppService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2PcieEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/Family/Hudson2/Hudson2PcieService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppHp.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppPortInit.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/GppReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/PcieEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/PcieLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/PcieMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Pcie/PcieReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/AhciEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/AhciLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/AhciLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/AhciMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Family/Hudson2/Hudson2SataEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Family/Hudson2/Hudson2SataResetService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Family/Hudson2/Hudson2SataService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Ide2AhciEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Ide2AhciLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Ide2AhciLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/Ide2AhciMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/RaidEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/RaidLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/RaidLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/RaidMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataEnvLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataIdeEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataIdeLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataIdeLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataIdeMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataLib.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sata/SataReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sd/Family/Hudson2/Hudson2SdEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sd/Family/Hudson2/Hudson2SdResetService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sd/Family/Hudson2/Hudson2SdService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sd/SdEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sd/SdLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Sd/SdMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/Family/Hudson2/Hudson2LpcEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/Family/Hudson2/Hudson2LpcResetService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/LpcEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/LpcLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/LpcMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/LpcReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/SpiEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/SpiLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/SpiMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Spi/SpiReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/EhciEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/EhciLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/EhciMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/EhciReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2EhciEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2EhciLateService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2EhciMidService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2OhciEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2OhciLateService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2OhciMidService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2XhciEnvService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2XhciLateService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2XhciMidService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/Family/Hudson2/Hudson2XhciResetService.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/OhciEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/OhciLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/OhciMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/OhciReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/UsbEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/UsbLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/UsbMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/UsbReset.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/XhciEnv.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/XhciLate.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/XhciMid.c
libagesa_srcs += $(AGESA_ROOT)/Proc/Fch/Usb/XhciReset.c

libagesa_objs = $(libagesa_srcs:$(src)/%.c=$(obj)/%.agesa_lib.o)
libagesa_objs += $(libagesa_srcs:$(src)/%.S=$(obj)/%.agesa_lib.o)

$(obj)/libagesa.a: $(libagesa_objs)
	@printf "    AGESA        $(subst $(obj)/,,$(@))\n"
	ar rcs $@ $+

# We could make a classes-y construct and have the buildsystem take care of this
# rule for us, but then we'd have to export $(AGESA_CFLAGS) and $(AGESA_INC)
# globally, and we're trying to avoid that. The only include paths which should
# be visible from outside are the $(AGESA_PUB_INC) paths.
$(obj)/%.agesa_lib.o: $(src)/%.c
	@printf "    CC-AGESA   $(subst $(obj)/,,$(@))\n"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(AGESA_CFLAGS) $(AGESA_INC) $(AGESA_PUB_INC) $^ -c -o $@

$(obj)/%.agesa_lib.o: $(src)/%.S
	@printf "    AS-AGESA   $(subst $(obj)/,,$(@))\n"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(AGESA_CFLAGS) $(AGESA_INC) $(AGESA_PUB_INC) $^ -c -o $@

romstage-libs  += $(obj)/libagesa.a
ramstage-libs  += $(obj)/libagesa.a
