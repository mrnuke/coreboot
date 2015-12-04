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

        Name(_HID, EISAID("PNP0A08"))	/* PCIe */
        Name(_CID, EISAID("PNP0A03"))   /* PCI */
        Name(_ADR, 0)
        Name(_BBN, 0)

Device (MCHC)
{
	Name (_ADR, 0x00000000)		/*Dev0 Func0 */

		OperationRegion (MCHP, PCI_Config, 0x00, 0x100)
		Field (MCHP, DWordAcc, NoLock, Preserve)
		{
			Offset(0xB4),
			BGSM,   32,     /* Base of Graphics Stolen Memory */
			Offset(0xBC),
			TLUD,   32,     /* Top of Low Useable DRAM */
		}
}

/* Current Resource Settings */
Method (_CRS, 0, Serialized)
{
	Name (MCRS, ResourceTemplate()
	{
		/* Bus Numbers */
		WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
				0x0000, 0x0000, 0x00ff, 0x0000, 0x0100,,,)

		/* IO Region 0 */
		DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
				0x0000, 0x0000, 0x0cf7, 0x0000, 0x0cf8,,,)

		/* PCI Config Space */
		Io (Decode16, 0x0cf8, 0x0cf8, 0x0001, 0x0008)

		/* IO Region 1 */
		DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
				0x0000, 0x01000, 0xffff, 0x0000, 0xf000,,,)

		/* VGA memory (0xa0000-0xbffff) */
		DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed,
				Cacheable, ReadWrite,
				0x00000000, 0x000a0000, 0x000bffff, 0x00000000,
				0x00020000,,,)

		/* Data and GFX stolen memory */
		DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed,
				Cacheable, ReadWrite,
				0x00000000, 0x3be00000, 0x3fffffff, 0x00000000,
				0x04200000,,, STOM)

		/* PCI MMIO Region (TOLUD - 0xcfffffff) */
		DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed,
				NonCacheable, ReadWrite,
				0x00000000, 0xa0000000, 0xcfffffff, 0x00000000,
				0x30000000,,, PM01)
	})

	/* Find PCI resource area in MCRS */
	CreateDwordField (MCRS, PM01._MIN, PMIN)
	CreateDwordField (MCRS, PM01._MAX, PMAX)
	CreateDwordField (MCRS, PM01._LEN, PLEN)

	/* Read C-Unit PCI CFG Reg. 0xBC for TOLUD (shadow from B-Unit) */
	And(^MCHC.TLUD, 0xFFF00000, PMIN)

	/* Calculate PCI MMIO Length */
	Add(Subtract(PMAX, PMIN), 1, PLEN)

	/* Find GFX resource area in GCRS */
	CreateDwordField(MCRS, STOM._MIN, GMIN)
	CreateDwordField(MCRS, STOM._MAX, GMAX)
	CreateDwordField(MCRS, STOM._LEN, GLEN)

	/* Read BGSM */
	And(^MCHC.BGSM, 0xFFF00000, GMIN)

	/* Read TOLUD */
	And(^MCHC.TLUD, 0xFFF00000, GMAX)
	Decrement(GMAX)

	Add(Subtract(GMAX, GMIN), 1, GLEN)

	Return (MCRS)
}

/* PCI IRQ assignment */
#include "pci_irqs.asl"
