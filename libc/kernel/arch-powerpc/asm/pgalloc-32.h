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
#ifndef _ASM_POWERPC_PGALLOC_32_H
#define _ASM_POWERPC_PGALLOC_32_H

#include <linux/threads.h>

#define MAX_PGTABLE_INDEX_SIZE 0

#define pmd_free(mm, x) do { } while (0)
#define __pmd_free_tlb(tlb,x,a) do { } while (0)

#define pmd_populate_kernel(mm, pmd, pte)   (pmd_val(*(pmd)) = __pa(pte) | _PMD_PRESENT)
#define pmd_populate(mm, pmd, pte)   (pmd_val(*(pmd)) = (page_to_pfn(pte) << PAGE_SHIFT) | _PMD_PRESENT)
#define pmd_pgtable(pmd) pmd_page(pmd)

#define check_pgt_cache() do { } while (0)
#endif
