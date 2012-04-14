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
#ifndef _ASM_POWERPC_PAGE_32_H
#define _ASM_POWERPC_PAGE_32_H

#define VM_DATA_DEFAULT_FLAGS VM_DATA_DEFAULT_FLAGS32

#define PTE_FLAGS_OFFSET 0

#define PTE_SHIFT (PAGE_SHIFT - PTE_T_LOG2)  

#ifndef __ASSEMBLY__

typedef unsigned long pte_basic_t;

struct page;

#include <asm-generic/getorder.h>

#define PGD_T_LOG2 (__builtin_ffs(sizeof(pgd_t)) - 1)
#define PTE_T_LOG2 (__builtin_ffs(sizeof(pte_t)) - 1)

#endif

#endif
