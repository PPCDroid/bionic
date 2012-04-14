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
#ifndef _ASM_POWERPC_PS3STOR_H_
#define _ASM_POWERPC_PS3STOR_H_

#include <linux/interrupt.h>

#include <asm/ps3.h>

struct ps3_storage_region {
 unsigned int id;
 u64 start;
 u64 size;
};

struct ps3_storage_device {
 struct ps3_system_bus_device sbd;

 struct ps3_dma_region dma_region;
 unsigned int irq;
 u64 blk_size;

 u64 tag;
 u64 lv1_status;
 struct completion done;

 unsigned long bounce_size;
 void *bounce_buf;
 u64 bounce_lpar;
 dma_addr_t bounce_dma;

 unsigned int num_regions;
 unsigned long accessible_regions;
 unsigned int region_idx;
 struct ps3_storage_region regions[0];
};

#endif
