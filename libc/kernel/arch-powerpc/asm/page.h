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
#ifndef _ASM_POWERPC_PAGE_H
#define _ASM_POWERPC_PAGE_H

#ifndef __ASSEMBLY__
#include <linux/types.h>
#else
#include <asm/types.h>
#endif
#include <asm/asm-compat.h>
#include <asm/kdump.h>

#define PAGE_SHIFT 12

#define PAGE_SIZE (ASM_CONST(1) << PAGE_SHIFT)

#ifndef __ASSEMBLY__
#define HPAGE_SHIFT PAGE_SHIFT
#define HPAGE_SIZE ((1UL) << HPAGE_SHIFT)
#define HPAGE_MASK (~(HPAGE_SIZE - 1))
#define HUGETLB_PAGE_ORDER (HPAGE_SHIFT - PAGE_SHIFT)
#define HUGE_MAX_HSTATE (MMU_PAGE_COUNT-1)
#endif

#define __HAVE_ARCH_GATE_AREA 1

#define PAGE_MASK (~((1 << PAGE_SHIFT) - 1))

#define KERNELBASE ASM_CONST(CONFIG_KERNEL_START)
#define PAGE_OFFSET ASM_CONST(CONFIG_PAGE_OFFSET)
#define LOAD_OFFSET ASM_CONST((CONFIG_KERNEL_START-CONFIG_PHYSICAL_START))

#define PHYSICAL_START ASM_CONST(CONFIG_PHYSICAL_START)

#define VIRT_PHYS_OFFSET (KERNELBASE - PHYSICAL_START)

#define MEMORY_START (PHYSICAL_START + PAGE_OFFSET - KERNELBASE)

#define virt_to_page(kaddr) pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#define pfn_to_kaddr(pfn) __va((pfn) << PAGE_SHIFT)
#define virt_addr_valid(kaddr) pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

#define __va(x) ((void *)(unsigned long)((phys_addr_t)(x) + PAGE_OFFSET - MEMORY_START))
#define __pa(x) ((unsigned long)(x) - PAGE_OFFSET + MEMORY_START)

#define VM_DATA_DEFAULT_FLAGS32 (VM_READ | VM_WRITE | VM_EXEC |   VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#define VM_DATA_DEFAULT_FLAGS64 (VM_READ | VM_WRITE |   VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#ifdef __powerpc64__
#include <asm/page_64.h>
#else
#include <asm/page_32.h>
#endif

#define _ALIGN_UP(addr,size) (((addr)+((size)-1))&(~((size)-1)))
#define _ALIGN_DOWN(addr,size) ((addr)&(~((size)-1)))

#define _ALIGN(addr,size) _ALIGN_UP(addr,size)

#define is_kernel_addr(x) ((x) >= PAGE_OFFSET)

#define PD_HUGE 0x80000000

#define HUGEPD_SHIFT_MASK 0x3f

#ifndef __ASSEMBLY__

#undef STRICT_MM_TYPECHECKS

#ifdef STRICT_MM_TYPECHECKS

typedef struct { pte_basic_t pte; } pte_t;
#define pte_val(x) ((x).pte)
#define __pte(x) ((pte_t) { (x) })

typedef struct { pte_t pte; } real_pte_t;

typedef struct { unsigned long pgd; } pgd_t;
#define pgd_val(x) ((x).pgd)
#define __pgd(x) ((pgd_t) { (x) })

typedef struct { unsigned long pgprot; } pgprot_t;
#define pgprot_val(x) ((x).pgprot)
#define __pgprot(x) ((pgprot_t) { (x) })

#else

typedef pte_basic_t pte_t;
#define pte_val(x) (x)
#define __pte(x) (x)

typedef pte_t real_pte_t;

typedef unsigned long pgd_t;
#define pgd_val(x) (x)
#define pgprot_val(x) (x)

typedef unsigned long pgprot_t;
#define __pgd(x) (x)
#define __pgprot(x) (x)

#endif

typedef struct { signed long pd; } hugepd_t;

#define is_hugepd(pdep) 0

struct page;

struct vm_area_struct;

typedef struct page *pgtable_t;

#include <asm-generic/memory_model.h>
#endif

#endif
