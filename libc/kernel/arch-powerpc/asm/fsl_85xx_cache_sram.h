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
#ifndef __ASM_POWERPC_FSL_85XX_CACHE_SRAM_H__
#define __ASM_POWERPC_FSL_85XX_CACHE_SRAM_H__

#include <asm/rheap.h>
#include <linux/spinlock.h>

struct mpc85xx_cache_sram {
 phys_addr_t base_phys;
 void *base_virt;
 unsigned int size;
 rh_info_t *rh;
 spinlock_t lock;
};

#endif
