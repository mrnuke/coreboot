/*
 * Definitions for the GPIO subsystem on Apollolake
 *
 * Placed in a separate file since some of these definitions can be used from
 * assembly code
 *
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _SOC_APOLLOLAKE_GPIO_DEFS_H_
#define _SOC_APOLLOLAKE_GPIO_DEFS_H_

#define PAD_CFG0_TX_DISABLE		(1 << 8)
#define PAD_CFG0_RX_DISABLE		(1 << 9)
#define PAD_CFG0_MODE_MASK		(7 << 10)
#define  PAD_CFG0_MODE_GPIO		(0 << 10)
#define  PAD_CFG0_MODE_FUNC(x)		((x) << 10)
#define PAD_CFG0_ROUTE_NMI		(1 << 17)
#define PAD_CFG0_ROUTE_SMI		(1 << 18)
#define PAD_CFG0_ROUTE_SCI		(1 << 19)
#define PAD_CFG0_ROUTE_IOAPIC		(1 << 20)
#define PAD_CFG0_RX_INVERT		(1 << 23)
#define PAD_CFG0_TRIG_MASK		(3 << 25)
#define  PAD_CFG0_TRIG_LEVEL		(0 << 25)
#define  PAD_CFG0_TRIG_EDGE_SINGLE	(1 << 25) /* controlled by RX_INVERT*/
#define  PAD_CFG0_TRIG_OFF		(2 << 25)
#define  PAD_CFG0_TRIG_EDGE_BOTH	(3 << 25)
#define PAD_CFG0_RESET_MASK		(3 << 30)
#define  PAD_CFG0_RESET_STICKY		(0 << 30)
#define  PAD_CFG0_RESET_DEEP		(1 << 30)
#define  PAD_CFG0_RESET_GPIOR		(2 << 30)
#define  PAD_CFG0_RESET_INACTIVE	(3 << 30)

#define PAD_CFG1_PULL_MASK		(0xf << 12)
#define  PAD_CFG1_PULL_NONE		(0x0 << 12)
#define  PAD_CFG1_PULL_DN_5K		(0x2 << 12)
#define  PAD_CFG1_PULL_DN_20K		(0x4 << 12)
#define  PAD_CFG1_PULL_UP_1K		(0x9 << 12)
#define  PAD_CFG1_PULL_UP_5K		(0xa << 12)
#define  PAD_CFG1_PULL_UP_2K		(0xb << 12)
#define  PAD_CFG1_PULL_UP_20K		(0xc << 12)
#define  PAD_CFG1_PULL_UP_667		(0xd << 12)
#define  PAD_CFG1_PULL_NATIVE		(0xf << 12)

#define PAD_CFG_BASE			0x500
#define PAD_CFG_OFFSET(pad)		(PAD_CFG_BASE + ((pad) * 8))

/* IOSF port numbers for GPIO comminuties*/
#define GPIO_SOUTHWEST			0xc0
#define GPIO_SOUTH			0xc2
#define GPIO_NORTHWEST			0xc4
#define GPIO_NORTH			0xc5
#define GPIO_WEST			0xc7

/* Special function pads in southwest community */
#define SMB_ALERTB			 31
#define SMB_CLK				 32
#define SMB_DATA			 33
#define LPC_ILB_SERIRQ			 34
#define LPC_CLKOUT0			 35
#define LPC_CLKOUT1			 36
#define LPC_AD0				 37
#define LPC_AD1				 38
#define LPC_AD2				 39
#define LPC_AD3				 40
#define LPC_CLKRUNB			 41
#define LPC_FRAMEB			 42

/* Default configurations */
#define PAD_CFG0_DEFAULT_FUNC(x)	(0x44000000 | PAD_CFG0_MODE_FUNC(x))
#define PAD_CFG0_DEFAULT_NATIVE		PAD_CFG0_DEFAULT_FUNC(1)

#define PAD_CFG1_DEFAULT_NOPULL		PAD_CFG1_PULL_NONE
#define PAD_CFG1_DEFAULT_PULLUP		PAD_CFG1_PULL_UP_20K
#define PAD_CFG1_DEFAULT_NATIVE			PAD_CFG1_PULL_NATIVE

#endif /* _SOC_APOLLOLAKE_GPIO_DEFS_H_ */
