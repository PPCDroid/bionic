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
#ifndef __POWERPC_KVM_PARA_H__
#define __POWERPC_KVM_PARA_H__

#include <linux/types.h>

struct kvm_vcpu_arch_shared {
 __u64 scratch1;
 __u64 scratch2;
 __u64 scratch3;
 __u64 critical;
 __u64 sprg0;
 __u64 sprg1;
 __u64 sprg2;
 __u64 sprg3;
 __u64 srr0;
 __u64 srr1;
 __u64 dar;
 __u64 msr;
 __u32 dsisr;
 __u32 int_pending;
 __u32 sr[16];
};

#define KVM_SC_MAGIC_R0 0x4b564d21  
#define HC_VENDOR_KVM (42 << 16)
#define HC_EV_SUCCESS 0
#define HC_EV_UNIMPLEMENTED 12

#define KVM_FEATURE_MAGIC_PAGE 1

#define KVM_MAGIC_FEAT_SR (1 << 0)

#endif
