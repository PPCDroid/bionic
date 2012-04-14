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
#ifndef _ASM_POWERPC_PAGE_64_H
#define _ASM_POWERPC_PAGE_64_H

#define HW_PAGE_SHIFT 12
#define HW_PAGE_SIZE (ASM_CONST(1) << HW_PAGE_SHIFT)
#define HW_PAGE_MASK (~(HW_PAGE_SIZE-1))

#define PAGE_FACTOR (PAGE_SHIFT - HW_PAGE_SHIFT)

#define SID_SHIFT 28
#define SID_MASK ASM_CONST(0xfffffffff)
#define ESID_MASK 0xfffffffff0000000UL
#define GET_ESID(x) (((x) >> SID_SHIFT) & SID_MASK)

#define SID_SHIFT_1T 40
#define SID_MASK_1T 0xffffffUL
#define ESID_MASK_1T 0xffffff0000000000UL
#define GET_ESID_1T(x) (((x) >> SID_SHIFT_1T) & SID_MASK_1T)

#ifndef __ASSEMBLY__
#include <asm/cache.h>

typedef unsigned long pte_basic_t;

#endif

#define slice_init()
#define get_slice_psize(mm, addr) MMU_PAGE_4K
#define slice_set_user_psize(mm, psize) do { BUG(); } while(0)

#define slice_set_range_psize(mm, start, len, psize)   slice_set_user_psize((mm), (psize))
#define slice_mm_new_context(mm) 1

#define VM_DATA_DEFAULT_FLAGS   (is_32bit_task() ?   VM_DATA_DEFAULT_FLAGS32 : VM_DATA_DEFAULT_FLAGS64)

#define VM_STACK_DEFAULT_FLAGS32 (VM_READ | VM_WRITE | VM_EXEC |   VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#define VM_STACK_DEFAULT_FLAGS64 (VM_READ | VM_WRITE |   VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#define VM_STACK_DEFAULT_FLAGS   (is_32bit_task() ?   VM_STACK_DEFAULT_FLAGS32 : VM_STACK_DEFAULT_FLAGS64)

#include <asm-generic/getorder.h>

#endif
