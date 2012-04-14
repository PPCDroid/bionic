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
#ifndef _XICS_H
#define _XICS_H

#include <linux/interrupt.h>

#define XICS_IPI 2
#define XICS_IRQ_SPURIOUS 0

#define DEFAULT_PRIORITY 5

#define IPI_PRIORITY 4

#define LOWEST_PRIORITY 0xFF

#define MAX_NUM_PRIORITIES 3

struct xics_cppr {
 unsigned char stack[MAX_NUM_PRIORITIES];
 int index;
};

#define xics_get_irq_server(virq, cpumask, strict_check) (xics_default_server)

#endif
