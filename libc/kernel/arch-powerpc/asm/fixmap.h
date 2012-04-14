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
#ifndef _ASM_FIXMAP_H
#define _ASM_FIXMAP_H

#ifndef __ASSEMBLY__
#include <linux/kernel.h>
#include <asm/page.h>

#define FIXADDR_TOP ((unsigned long)(-PAGE_SIZE))

enum fixed_addresses {
 FIX_HOLE,

 FIX_EARLY_DEBUG_TOP = FIX_HOLE,
 FIX_EARLY_DEBUG_BASE = FIX_EARLY_DEBUG_TOP+((128*1024)/PAGE_SIZE)-1,

 __end_of_fixed_addresses
};

#define set_fixmap(idx, phys)   __set_fixmap(idx, phys, PAGE_KERNEL)

#define set_fixmap_nocache(idx, phys)   __set_fixmap(idx, phys, PAGE_KERNEL_NCG)

#define clear_fixmap(idx)   __set_fixmap(idx, 0, __pgprot(0))

#define __FIXADDR_SIZE (__end_of_fixed_addresses << PAGE_SHIFT)
#define FIXADDR_START (FIXADDR_TOP - __FIXADDR_SIZE)

#define __fix_to_virt(x) (FIXADDR_TOP - ((x) << PAGE_SHIFT))
#define __virt_to_fix(x) ((FIXADDR_TOP - ((x)&PAGE_MASK)) >> PAGE_SHIFT)

#endif
#endif
