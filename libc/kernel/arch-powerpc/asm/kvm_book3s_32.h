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
#ifndef __ASM_KVM_BOOK3S_32_H__
#define __ASM_KVM_BOOK3S_32_H__

#define PTE_SIZE 12
#define VSID_ALL 0
#define SR_INVALID 0x00000001  
#define SR_KP 0x20000000
#define PTE_V 0x80000000
#define PTE_SEC 0x00000040
#define PTE_M 0x00000010
#define PTE_R 0x00000100
#define PTE_C 0x00000080
#define SID_SHIFT 28
#define ESID_MASK 0xf0000000
#define VSID_MASK 0x00fffffff0000000ULL
#endif
