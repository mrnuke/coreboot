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

        Name(_HID, EISAID("PNP0A08"))	// PCIe
        Name(_CID, EISAID("PNP0A03"))   // PCI
        Name(_ADR, 0)
        Name(_BBN, 0)

/* PCI IRQ assignment */
#include "pci_irqs.asl"
