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
#ifndef __EHV_PIC_H__
#define __EHV_PIC_H__

#include <linux/irq.h>

#define NR_EHV_PIC_INTS 1024

#define EHV_PIC_INFO(name) EHV_PIC_##name

#define EHV_PIC_VECPRI_POLARITY_NEGATIVE 0
#define EHV_PIC_VECPRI_POLARITY_POSITIVE 1
#define EHV_PIC_VECPRI_SENSE_EDGE 0
#define EHV_PIC_VECPRI_SENSE_LEVEL 0x2
#define EHV_PIC_VECPRI_POLARITY_MASK 0x1
#define EHV_PIC_VECPRI_SENSE_MASK 0x2

struct ehv_pic {

 struct irq_host *irqhost;

 struct irq_chip hc_irq;

 int coreint_flag;
};

#endif
