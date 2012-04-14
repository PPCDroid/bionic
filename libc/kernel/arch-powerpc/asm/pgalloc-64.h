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
#ifndef _ASM_POWERPC_PGALLOC_64_H
#define _ASM_POWERPC_PGALLOC_64_H

#include <linux/slab.h>
#include <linux/cpumask.h>
#include <linux/percpu.h>

struct vmemmap_backing {
 struct vmemmap_backing *list;
 unsigned long phys;
 unsigned long virt_addr;
};

#define MAX_PGTABLE_INDEX_SIZE 0xf

#define PGT_CACHE(shift) (pgtable_cache[(shift)-1])

#define pgd_populate(MM, PGD, PUD) pgd_set(PGD, PUD)
#define pmd_populate(mm, pmd, pte_page)   pmd_populate_kernel(mm, pmd, page_address(pte_page))
#define pmd_populate_kernel(mm, pmd, pte) pmd_set(pmd, (unsigned long)(pte))
#define pmd_pgtable(pmd) pmd_page(pmd)
#define __pmd_free_tlb(tlb, pmd, addr)   pgtable_free_tlb(tlb, pmd, PMD_INDEX_SIZE)
#define __pud_free_tlb(tlb, pud, addr)   pgtable_free_tlb(tlb, pud, PUD_INDEX_SIZE)
#define check_pgt_cache() do { } while (0)
#endif
