/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef __ASM_POWERPC_LIBATA_PORTMAP_H
#define __ASM_POWERPC_LIBATA_PORTMAP_H

#define ATA_PRIMARY_CMD 0x1F0
#define ATA_PRIMARY_CTL 0x3F6
#define ATA_PRIMARY_IRQ(dev) pci_get_legacy_ide_irq(dev, 0)

#define ATA_SECONDARY_CMD 0x170
#define ATA_SECONDARY_CTL 0x376
#define ATA_SECONDARY_IRQ(dev) pci_get_legacy_ide_irq(dev, 1)

#endif
