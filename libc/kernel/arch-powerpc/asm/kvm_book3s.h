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
#ifndef __ASM_KVM_BOOK3S_H__
#define __ASM_KVM_BOOK3S_H__

#include <linux/types.h>
#include <linux/kvm_host.h>
#include <asm/kvm_book3s_asm.h>

struct kvmppc_bat {
 u64 raw;
 u32 bepi;
 u32 bepi_mask;
 u32 brpn;
 u8 wimg;
 u8 pp;
 bool vs : 1;
 bool vp : 1;
};

struct kvmppc_sid_map {
 u64 guest_vsid;
 u64 guest_esid;
 u64 host_vsid;
 bool valid : 1;
};

#define SID_MAP_BITS 9
#define SID_MAP_NUM (1 << SID_MAP_BITS)
#define SID_MAP_MASK (SID_MAP_NUM - 1)

#define SID_CONTEXTS 128
#define VSID_POOL_SIZE (SID_CONTEXTS * 16)

struct hpte_cache {
 struct hlist_node list_pte;
 struct hlist_node list_pte_long;
 struct hlist_node list_vpte;
 struct hlist_node list_vpte_long;
 struct rcu_head rcu_head;
 u64 host_va;
 u64 pfn;
 ulong slot;
 struct kvmppc_pte pte;
};

struct kvmppc_vcpu_book3s {
 struct kvm_vcpu vcpu;
 struct kvmppc_book3s_shadow_vcpu *shadow_vcpu;
 struct kvmppc_sid_map sid_map[SID_MAP_NUM];
 struct {
 u64 esid;
 u64 vsid;
 } slb_shadow[64];
 u8 slb_shadow_max;
 struct kvmppc_bat ibat[8];
 struct kvmppc_bat dbat[8];
 u64 hid[6];
 u64 gqr[8];
 u64 sdr1;
 u64 hior;
 u64 msr_mask;
 u64 vsid_next;
 u64 vsid_first;
 u64 vsid_max;
 int context_id[SID_CONTEXTS];

 struct hlist_head hpte_hash_pte[HPTEG_HASH_NUM_PTE];
 struct hlist_head hpte_hash_pte_long[HPTEG_HASH_NUM_PTE_LONG];
 struct hlist_head hpte_hash_vpte[HPTEG_HASH_NUM_VPTE];
 struct hlist_head hpte_hash_vpte_long[HPTEG_HASH_NUM_VPTE_LONG];
 int hpte_cache_count;
 spinlock_t mmu_lock;
};

#define CONTEXT_HOST 0
#define CONTEXT_GUEST 1
#define CONTEXT_GUEST_END 2

#define VSID_REAL 0x1fffffffffc00000ULL
#define VSID_BAT 0x1fffffffffb00000ULL
#define VSID_REAL_DR 0x2000000000000000ULL
#define VSID_REAL_IR 0x4000000000000000ULL
#define VSID_PR 0x8000000000000000ULL

#define OSI_SC_MAGIC_R3 0x113724FA
#define OSI_SC_MAGIC_R4 0x77810F9B
#define INS_DCBZ 0x7c0007ec
#endif
