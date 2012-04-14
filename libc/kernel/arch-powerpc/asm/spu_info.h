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
#ifndef _SPU_INFO_H
#define _SPU_INFO_H

#include <linux/types.h>

struct mfc_cq_sr {
 __u64 mfc_cq_data0_RW;
 __u64 mfc_cq_data1_RW;
 __u64 mfc_cq_data2_RW;
 __u64 mfc_cq_data3_RW;
};

struct spu_dma_info {
 __u64 dma_info_type;
 __u64 dma_info_mask;
 __u64 dma_info_status;
 __u64 dma_info_stall_and_notify;
 __u64 dma_info_atomic_command_status;
 struct mfc_cq_sr dma_info_command_data[16];
};

struct spu_proxydma_info {
 __u64 proxydma_info_type;
 __u64 proxydma_info_mask;
 __u64 proxydma_info_status;
 struct mfc_cq_sr proxydma_info_command_data[8];
};

#endif
