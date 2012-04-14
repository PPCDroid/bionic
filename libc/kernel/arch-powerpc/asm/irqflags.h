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
#ifndef _ASM_IRQFLAGS_H
#define _ASM_IRQFLAGS_H

#ifndef __ASSEMBLY__

#include <asm/hw_irq.h>

#else
#define TRACE_ENABLE_INTS
#define TRACE_DISABLE_INTS
#define TRACE_AND_RESTORE_IRQ_PARTIAL(en,skip)
#define TRACE_AND_RESTORE_IRQ(en)   stb en,PACASOFTIRQEN(r13)
#endif

#endif
