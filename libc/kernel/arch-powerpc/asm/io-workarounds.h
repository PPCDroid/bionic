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
#ifndef _IO_WORKAROUNDS_H
#define _IO_WORKAROUNDS_H

#include <linux/io.h>
#include <asm/pci-bridge.h>

struct iowa_bus {
 struct pci_controller *phb;
 struct ppc_pci_io *ops;
 void *private;
};

struct iowa_bus *iowa_mem_find_bus(const PCI_IO_ADDR);
struct iowa_bus *iowa_pio_find_bus(unsigned long);

#define SPIDER_PCI_REG_BASE 0xd000
#define SPIDER_PCI_REG_SIZE 0x1000
#define SPIDER_PCI_VCI_CNTL_STAT 0x0110
#define SPIDER_PCI_DUMMY_READ 0x0810
#define SPIDER_PCI_DUMMY_READ_BASE 0x0814

#endif
