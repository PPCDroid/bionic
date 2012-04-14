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
#ifndef _ASM_POWERPC_DBELL_H
#define _ASM_POWERPC_DBELL_H

#include <linux/smp.h>
#include <linux/threads.h>

#include <asm/ppc-opcode.h>

#define PPC_DBELL_MSG_BRDCAST (0x04000000)
#define PPC_DBELL_TYPE(x) (((x) & 0xf) << (63-36))
enum ppc_dbell {
 PPC_DBELL = 0,
 PPC_DBELL_CRIT = 1,
 PPC_G_DBELL = 2,
 PPC_G_DBELL_CRIT = 3,
 PPC_G_DBELL_MC = 4,
};

#endif
