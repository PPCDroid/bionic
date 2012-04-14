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
#ifndef _ASM_POWERPC_PGTABLE_PPC32_H
#define _ASM_POWERPC_PGTABLE_PPC32_H

#include <asm-generic/pgtable-nopmd.h>

#ifndef __ASSEMBLY__
#include <linux/sched.h>
#include <linux/threads.h>
#include <asm/io.h>  

#endif

#define PGDIR_SHIFT (PAGE_SHIFT + PTE_SHIFT)
#define PGDIR_SIZE (1UL << PGDIR_SHIFT)
#define PGDIR_MASK (~(PGDIR_SIZE-1))

#ifndef __ASSEMBLY__
#define PTE_TABLE_SIZE (sizeof(pte_t) << PTE_SHIFT)
#define PGD_TABLE_SIZE (sizeof(pgd_t) << (32 - PGDIR_SHIFT))
#endif

#define PTRS_PER_PTE (1 << PTE_SHIFT)
#define PTRS_PER_PMD 1
#define PTRS_PER_PGD (1 << (32 - PGDIR_SHIFT))

#define USER_PTRS_PER_PGD (TASK_SIZE / PGDIR_SIZE)
#define FIRST_USER_ADDRESS 0

#define pte_ERROR(e)   printk("%s:%d: bad pte %llx.\n", __FILE__, __LINE__,   (unsigned long long)pte_val(e))
#define pgd_ERROR(e)   printk("%s:%d: bad pgd %08lx.\n", __FILE__, __LINE__, pgd_val(e))

#define KVIRT_TOP (0xfe000000UL)  

#define IOREMAP_TOP KVIRT_TOP

#define VMALLOC_OFFSET (0x1000000)  
#ifdef PPC_PIN_SIZE
#define VMALLOC_START (((_ALIGN((long)high_memory, PPC_PIN_SIZE) + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1)))
#else
#define VMALLOC_START ((((long)high_memory + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1)))
#endif
#define VMALLOC_END ioremap_bot

#include <asm/pte-hash32.h>

#include <asm/pte-common.h>

#ifndef __ASSEMBLY__

#define pte_clear(mm, addr, ptep)   do { pte_update(ptep, ~_PAGE_HASHPTE, 0); } while (0)

#define pmd_none(pmd) (!pmd_val(pmd))
#define pmd_bad(pmd) (pmd_val(pmd) & _PMD_BAD)
#define pmd_present(pmd) (pmd_val(pmd) & _PMD_PRESENT_MASK)
#define pmd_clear(pmdp) do { pmd_val(*(pmdp)) = 0; } while (0)

#ifdef PTE_ATOMIC_UPDATES
#else
#endif
#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
#if _PAGE_HASHPTE != 0
#endif
#define ptep_test_and_clear_young(__vma, __addr, __ptep)   __ptep_test_and_clear_young((__vma)->vm_mm->context.id, __addr, __ptep)
#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
#define __HAVE_ARCH_PTEP_SET_WRPROTECT
#define __HAVE_ARCH_PTE_SAME
#define pte_same(A,B) (((pte_val(A) ^ pte_val(B)) & ~_PAGE_HASHPTE) == 0)
#define pmd_page_vaddr(pmd)   ((unsigned long) __va(pmd_val(pmd) & PAGE_MASK))
#define pmd_page(pmd)   pfn_to_page(pmd_val(pmd) >> PAGE_SHIFT)
#define pgd_offset_k(address) pgd_offset(&init_mm, address)
#define pgd_index(address) ((address) >> PGDIR_SHIFT)
#define pgd_offset(mm, address) ((mm)->pgd + pgd_index(address))
#define pte_index(address)   (((address) >> PAGE_SHIFT) & (PTRS_PER_PTE - 1))
#define pte_offset_kernel(dir, addr)   ((pte_t *) pmd_page_vaddr(*(dir)) + pte_index(addr))
#define pte_offset_map(dir, addr)   ((pte_t *) kmap_atomic(pmd_page(*(dir))) + pte_index(addr))
#define pte_unmap(pte) kunmap_atomic(pte)
#define __swp_type(entry) ((entry).val & 0x1f)
#define __swp_offset(entry) ((entry).val >> 5)
#define __swp_entry(type, offset) ((swp_entry_t) { (type) | ((offset) << 5) })
#define __pte_to_swp_entry(pte) ((swp_entry_t) { pte_val(pte) >> 3 })
#define __swp_entry_to_pte(x) ((pte_t) { (x).val << 3 })
#define PTE_FILE_MAX_BITS 29
#define pte_to_pgoff(pte) (pte_val(pte) >> 3)
#define pgoff_to_pte(off) ((pte_t) { ((off) << 3) | _PAGE_FILE })
#define pgtable_cache_init() do { } while (0)

#endif

#endif
