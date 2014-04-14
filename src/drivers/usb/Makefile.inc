romstage-$(CONFIG_USBDEBUG_IN_ROMSTAGE) += ehci_debug.c pci_ehci.c console.c

ramstage-$(CONFIG_USBDEBUG) += ehci_debug.c pci_ehci.c console.c

smm-$(CONFIG_HAVE_SMI_HANDLER) += ehci_debug.c pci_ehci.c console.c
