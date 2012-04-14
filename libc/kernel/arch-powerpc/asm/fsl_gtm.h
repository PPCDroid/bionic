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
#ifndef __ASM_FSL_GTM_H
#define __ASM_FSL_GTM_H

#include <linux/types.h>

struct gtm;

struct gtm_timer {
 unsigned int irq;

 struct gtm *gtm;
 bool requested;
 u8 __iomem *gtcfr;
 __be16 __iomem *gtmdr;
 __be16 __iomem *gtpsr;
 __be16 __iomem *gtcnr;
 __be16 __iomem *gtrfr;
 __be16 __iomem *gtevr;
};

#endif
