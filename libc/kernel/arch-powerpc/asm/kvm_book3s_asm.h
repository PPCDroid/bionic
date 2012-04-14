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
#ifndef __ASM_KVM_BOOK3S_ASM_H__
#define __ASM_KVM_BOOK3S_ASM_H__

#ifdef __ASSEMBLY__

#else

struct kvmppc_book3s_shadow_vcpu {
 ulong gpr[14];
 u32 cr;
 u32 xer;

 u32 fault_dsisr;
 u32 last_inst;
 ulong ctr;
 ulong lr;
 ulong pc;
 ulong shadow_srr1;
 ulong fault_dar;

};

#endif

#endif
