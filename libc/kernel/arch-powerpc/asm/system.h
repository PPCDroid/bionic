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
#ifndef _ASM_POWERPC_SYSTEM_H
#define _ASM_POWERPC_SYSTEM_H

#include <linux/kernel.h>
#include <linux/irqflags.h>

#include <asm/hw_irq.h>

#define mb() __asm__ __volatile__ ("sync" : : : "memory")
#define rmb() __asm__ __volatile__ ("sync" : : : "memory")
#define wmb() __asm__ __volatile__ ("sync" : : : "memory")
#define read_barrier_depends() do { } while(0)

#define set_mb(var, value) do { var = value; mb(); } while (0)

#endif
