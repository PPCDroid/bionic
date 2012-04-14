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
#ifndef __ASM_KVM_FPU_H__
#define __ASM_KVM_FPU_H__

#include <linux/types.h>

#define FPD_ONE_IN(name) extern void fpd_ ## name(u64 *fpscr, u32 *cr,   u64 *dst, u64 *src1);
#define FPD_TWO_IN(name) extern void fpd_ ## name(u64 *fpscr, u32 *cr,   u64 *dst, u64 *src1, u64 *src2);
#define FPD_THREE_IN(name) extern void fpd_ ## name(u64 *fpscr, u32 *cr,   u64 *dst, u64 *src1, u64 *src2, u64 *src3);

#endif
