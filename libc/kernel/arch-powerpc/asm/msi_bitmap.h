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
#ifndef _POWERPC_SYSDEV_MSI_BITMAP_H
#define _POWERPC_SYSDEV_MSI_BITMAP_H

#include <linux/of.h>
#include <asm/irq.h>

struct msi_bitmap {
 struct device_node *of_node;
 unsigned long *bitmap;
 spinlock_t lock;
 unsigned int irq_count;
};

#endif
