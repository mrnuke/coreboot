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

Method(_PRT)
{
	Return(Package() {

	       Package(){0x0000FFFF, 0, 0, 16},		/* NPK */
	       Package(){0x0000FFFF, 1, 0, 24},		/* DPTF */
	       Package(){0x0002FFFF, 0, 0, 19},		/* GEN */
	       Package(){0x0003FFFF, 0, 0, 21},		/* IUNIT */
	       Package(){0x000DFFFF, 1, 0, 40},		/* PMC */
	       Package(){0x000EFFFF, 0, 0, 25},		/* Audio */
	       Package(){0x000FFFFF, 0, 0, 20},		/* CSE */
	       Package(){0x0011FFFF, 0, 0, 26},		/* ISH */
	       Package(){0x0012FFFF, 0, 0, 19},		/* SATA */
	       Package(){0x0013FFFF, 0, 0, 22},		/* PCIe-A 0 */
	       Package(){0x0014FFFF, 0, 0, 22},		/* PCIe-B 0 */
	       Package(){0x0015FFFF, 0, 0, 17},		/* xHCI */
	       Package(){0x0015FFFF, 1, 0, 13},		/* xDCI */
	       Package(){0x0016FFFF, 0, 0, 27},		/* I2C0 */
	       Package(){0x0016FFFF, 1, 0, 28},		/* I2C1 */
	       Package(){0x0016FFFF, 2, 0, 29},		/* I2C2 */
	       Package(){0x0016FFFF, 3, 0, 30},		/* I2C3 */
	       Package(){0x0017FFFF, 0, 0, 31},		/* I2C4 */
	       Package(){0x0017FFFF, 1, 0, 32},		/* I2C5 */
	       Package(){0x0017FFFF, 2, 0, 33},		/* I2C6 */
	       Package(){0x0017FFFF, 3, 0, 34},		/* I2C7 */
	       Package(){0x0018FFFF, 0, 0, 4},		/* UART0 */
	       Package(){0x0018FFFF, 1, 0, 5},		/* UART1 */
	       Package(){0x0018FFFF, 2, 0, 6},		/* UART2 */
	       Package(){0x0018FFFF, 3, 0, 7},		/* UART3 */
	       Package(){0x0019FFFF, 0, 0, 35},		/* SPI0 */
	       Package(){0x0019FFFF, 1, 0, 36},		/* SPI1 */
	       Package(){0x0019FFFF, 2, 0, 37},		/* SPI2 */
	       Package(){0x001BFFFF, 0, 0, 3},		/* SDCard */
	       Package(){0x001CFFFF, 0, 0, 39},		/* eMMC */
	       Package(){0x001EFFFF, 0, 0, 42},		/* SDIO */
	       Package(){0x001FFFFF, 0, 0, 20},		/* LPC */
	       }
	)
}
