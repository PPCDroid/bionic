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
#ifndef _ASM_POWERPC_ASYNC_TX_H_
#define _ASM_POWERPC_ASYNC_TX_H_

#define async_tx_find_channel(dep, type, dst, dst_count, src, src_count, len)   __async_tx_find_channel(dep, type)

struct dma_chan *
__async_tx_find_channel(struct async_submit_ctl *submit,
 enum dma_transaction_type tx_type);

#endif
