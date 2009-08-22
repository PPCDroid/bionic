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
#ifndef __LINUX_KVM_POWERPC_H
#define __LINUX_KVM_POWERPC_H

#include <asm/types.h>

struct kvm_regs {
 __u64 pc;
 __u64 cr;
 __u64 ctr;
 __u64 lr;
 __u64 xer;
 __u64 msr;
 __u64 srr0;
 __u64 srr1;
 __u64 pid;

 __u64 sprg0;
 __u64 sprg1;
 __u64 sprg2;
 __u64 sprg3;
 __u64 sprg4;
 __u64 sprg5;
 __u64 sprg6;
 __u64 sprg7;

 __u64 gpr[32];
};

struct kvm_sregs {
};

struct kvm_fpu {
 __u64 fpr[32];
};

#endif
