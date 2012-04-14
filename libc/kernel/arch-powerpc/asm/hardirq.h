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
#ifndef _ASM_POWERPC_HARDIRQ_H
#define _ASM_POWERPC_HARDIRQ_H

#include <linux/threads.h>
#include <linux/irq.h>

typedef struct {
 unsigned int __softirq_pending;
 unsigned int timer_irqs;
 unsigned int pmu_irqs;
 unsigned int mce_exceptions;
 unsigned int spurious_irqs;
} ____cacheline_aligned irq_cpustat_t;

#define __ARCH_IRQ_STAT

#define local_softirq_pending() __get_cpu_var(irq_stat).__softirq_pending

#define arch_irq_stat_cpu arch_irq_stat_cpu

#endif
