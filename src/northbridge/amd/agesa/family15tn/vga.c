#include "vgareplay.h"

#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>

static void radeon_native_init(device_t dev)
{
	print_debug("======================================================\n");
	print_debug("== replay ricola\n");
	print_debug("======================================================\n");


	printk(BIOS_DEBUG, "Initializing VGA via replay...\n");

	run_replay();
	pci_dev_init(dev);

	printk(BIOS_DEBUG, "Attempting to turn screen on via replay...\n");
	replay_int10_r1();
	replay_int10_r2();
	replay_int10_r3();

	printk(BIOS_DEBUG, "Enabled VGA, but did it work?\n");

}

static void radeon_native_enable(device_t dev)
{
}

static void radeon_native_disable(device_t dev)
{
}

static struct device_operations radeon_operations = {
	.read_resources = pci_dev_read_resources,
	.set_resources = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init = radeon_native_init,
	.disable = radeon_native_disable,
	.enable = radeon_native_enable,
	.ops_pci = 0,
};

static const struct pci_driver radeon_driver __pci_driver = {
	.ops = &radeon_operations,
	.vendor = PCI_VENDOR_ID_ATI,
	.device = 0x9900,
};
