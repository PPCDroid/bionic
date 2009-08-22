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
#ifndef _ASM_POWERPC_SIGINFO_H
#define _ASM_POWERPC_SIGINFO_H

#ifdef __powerpc64__
#define __ARCH_SI_PREAMBLE_SIZE (4 * sizeof(int))
#define SI_PAD_SIZE32 ((SI_MAX_SIZE/sizeof(int)) - 3)
#endif

#include <asm-generic/siginfo.h>

#undef NSIGTRAP
#define NSIGTRAP 4

#endif
