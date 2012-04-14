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
#ifndef _ASM_POWERPC_DEVICE_H
#define _ASM_POWERPC_DEVICE_H

struct dma_map_ops;
struct device_node;

struct dev_archdata {

 struct dma_map_ops *dma_ops;

 union {
 dma_addr_t dma_offset;
 void *iommu_table_base;
 } dma_data;

};

struct pdev_archdata {
 u64 dma_mask;
};

#define ARCH_HAS_DMA_GET_REQUIRED_MASK

#endif
