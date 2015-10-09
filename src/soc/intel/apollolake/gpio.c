/*
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

#include <soc/gpio.h>
#include <soc/iosf.h>

void gpio_configure_pad(const struct pad_config *cfg)
{
	uint16_t config_offset = PAD_CFG_OFFSET(cfg->pad);
	iosf_write(cfg->community, config_offset, cfg->config[0]);
	iosf_write(cfg->community, config_offset + 4, cfg->config[1]);
}
