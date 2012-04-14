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
#ifndef _ASM_POWERPC_IDE_H
#define _ASM_POWERPC_IDE_H

#include <linux/compiler.h>
#include <asm/io.h>

#define __ide_mm_insw(p, a, c) readsw((void __iomem *)(p), (a), (c))
#define __ide_mm_insl(p, a, c) readsl((void __iomem *)(p), (a), (c))
#define __ide_mm_outsw(p, a, c) writesw((void __iomem *)(p), (a), (c))
#define __ide_mm_outsl(p, a, c) writesl((void __iomem *)(p), (a), (c))

#endif
