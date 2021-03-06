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
#ifndef _ASM_POWERPC_SIGCONTEXT_H
#define _ASM_POWERPC_SIGCONTEXT_H

#include <asm/ptrace.h>
#ifdef __powerpc64__
#include <asm/elf.h>
#endif

struct sigcontext {
 unsigned long _unused[4];
 int signal;
#ifdef __powerpc64__
 int _pad0;
#endif
 unsigned long handler;
 unsigned long oldmask;
 struct pt_regs *regs;
#ifdef __powerpc64__
 elf_gregset_t gp_regs;
 elf_fpregset_t fp_regs;

 elf_vrreg_t *v_regs;
 long vmx_reserve[ELF_NVRREG+ELF_NVRREG+32+1];
#endif
};

#endif
