/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <device/device.h>
#include <soc/gpio.h>

/* TODO: Move GPIO config to its own file once we get more GPIOs in the list */
static const struct pad_config aplk_rvp_gpios[] = {
	PAD_CFG_GPO(GPIO_22, 1, DEEP),			/* SATA Direct power */
	PAD_CFG_NF(GPIO_46, NATIVE, DEEP, NF1),		/* UART2 RX*/
	PAD_CFG_NF(GPIO_47, NATIVE, DEEP, NF1),		/* UART2 TX*/
	PAD_CFG_NF(GPIO_193, NATIVE, DEEP, NF1),	/* PANEL0_VDDEN */
	PAD_CFG_NF(GPIO_194, NATIVE, DEEP, NF1),	/* PANEL0_BKLTEN */
	PAD_CFG_NF(GPIO_195, NATIVE, DEEP, NF1),	/* PANEL0_BKLTCTL */
	PAD_CFG_NF(GPIO_209, NATIVE, DEEP, NF1),	/* PCIE_CLKREQ0_B */
	PAD_CFG_NF(GPIO_210, NATIVE, DEEP, NF1),	/* PCIE_CLKREQ1_B */
	PAD_CFG_NF(GPIO_211, NATIVE, DEEP, NF1),	/* PCIE_CLKREQ2_B */
	PAD_CFG_NF(GPIO_212, NATIVE, DEEP, NF1),	/* PCIE_CLKREQ3_B */
};

static void mainboard_init(void *chip_info)
{
	gpio_configure_pads(aplk_rvp_gpios, ARRAY_SIZE(aplk_rvp_gpios));
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
};
