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
#ifndef _ASM_POWERPC_EMULATED_OPS_H
#define _ASM_POWERPC_EMULATED_OPS_H

#include <linux/atomic.h>
#include <linux/perf_event.h>

#define __PPC_WARN_EMULATED(type) do { } while (0)

#define PPC_WARN_EMULATED(type, regs)   do {   perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,   1, regs, 0);   __PPC_WARN_EMULATED(type);   } while (0)

#define PPC_WARN_ALIGNMENT(type, regs)   do {   perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS,   1, regs, regs->dar);   __PPC_WARN_EMULATED(type);   } while (0)

#endif
