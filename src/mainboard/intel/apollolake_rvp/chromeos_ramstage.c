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

#include <boot/coreboot_tables.h>
#include <vendorcode/google/chromeos/chromeos.h>

#define GPIO_COUNT 7

void fill_lb_gpios(struct lb_gpios *gpios)
{
	struct lb_gpio *gpio;

	gpios->size = sizeof(*gpios) + (GPIO_COUNT * sizeof(struct lb_gpio));
	gpios->count = GPIO_COUNT;

	gpio = gpios->gpios;
	fill_lb_gpio(gpio++, -1, ACTIVE_HIGH, "recovery", 0);
	fill_lb_gpio(gpio++, -1, ACTIVE_HIGH, "developer", 1);
	fill_lb_gpio(gpio++, -1, ACTIVE_HIGH, "lid", 1);
	fill_lb_gpio(gpio++, -1, ACTIVE_HIGH, "power", 0);
	fill_lb_gpio(gpio++, -1, ACTIVE_HIGH, "oprom", 0);
	fill_lb_gpio(gpio++, -1, ACTIVE_HIGH, "write protect", 0);
}
