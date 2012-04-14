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
#ifndef __ASM_44X_H__
#define __ASM_44X_H__

#include <linux/kvm_host.h>

#define PPC44x_TLB_SIZE 64

#define KVM44x_GUEST_TLB_SIZE 64

struct kvmppc_44x_tlbe {
 u32 tid;
 u32 word0;
 u32 word1;
 u32 word2;
};

struct kvmppc_44x_shadow_ref {
 struct page *page;
 u16 gtlb_index;
 u8 writeable;
 u8 tid;
};

struct kvmppc_vcpu_44x {

 struct kvmppc_44x_tlbe guest_tlb[KVM44x_GUEST_TLB_SIZE];

 struct kvmppc_44x_shadow_ref shadow_refs[PPC44x_TLB_SIZE];

 struct kvmppc_44x_tlbe shadow_tlb[PPC44x_TLB_SIZE];
 u8 shadow_tlb_mod[PPC44x_TLB_SIZE];

 struct kvm_vcpu vcpu;
};

#endif
