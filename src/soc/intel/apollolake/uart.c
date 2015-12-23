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

#include <console/uart.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <soc/pci_ids.h>

/*
 * Shadow BAR for console UART:
 * This allows us to keep track of the actual MMIO region without needing to
 * pci_dev_locate()/pci_read_config32() on every uart_platform_base() call.
 */
static uintptr_t uart_bar = CONFIG_CONSOLE_UART_BASE_ADDRESS;

uintptr_t uart_platform_base(int idx)
{
	return uart_bar;
}

unsigned int uart_platform_refclk(void)
{
	/* That's within 0.5% of the actual value we've set earlier */
	return 115200 * 16;
}

static void update_uart_bar(struct device *dev)
{
	uart_bar = find_resource(dev, PCI_BASE_ADDRESS_0)->base;
}

static void uart_set_resources(struct device *dev)
{
	if (dev->path.pci.devfn == PCI_DEVFN(0x18, CONFIG_UART_FOR_CONSOLE))
		update_uart_bar(dev);

	pci_dev_set_resources(dev);
}

static struct device_operations uart_ops = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = uart_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = pci_dev_init,
	.enable           = DEVICE_NOOP
};

static const unsigned short uart_ids[] = {
	PCI_DEV_ID_APOLLOLAKE_UART0, PCI_DEV_ID_APOLLOLAKE_UART1,
	PCI_DEV_ID_APOLLOLAKE_UART2, PCI_DEV_ID_APOLLOLAKE_UART3,
	0
};

static const struct pci_driver uart_driver __pci_driver = {
	.ops     = &uart_ops,
	.vendor  = PCI_VENDOR_ID_INTEL,
	.devices = uart_ids
};
