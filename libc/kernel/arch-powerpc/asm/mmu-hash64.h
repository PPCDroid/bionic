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
#ifndef _ASM_POWERPC_MMU_HASH64_H_
#define _ASM_POWERPC_MMU_HASH64_H_

#include <asm/asm-compat.h>
#include <asm/page.h>

#define STE_ESID_V 0x80
#define STE_ESID_KS 0x20
#define STE_ESID_KP 0x10
#define STE_ESID_N 0x08

#define STE_VSID_SHIFT 12

#define STAB0_PAGE 0x8
#define STAB0_OFFSET (STAB0_PAGE << 12)
#define STAB0_PHYS_ADDR (STAB0_OFFSET + PHYSICAL_START)

#ifndef __ASSEMBLY__

#endif

#define SLB_NUM_BOLTED 3
#define SLB_CACHE_ENTRIES 8
#define SLB_MIN_SIZE 32

#define SLB_ESID_V ASM_CONST(0x0000000008000000)  

#define SLB_VSID_SHIFT 12
#define SLB_VSID_SHIFT_1T 24
#define SLB_VSID_SSIZE_SHIFT 62
#define SLB_VSID_B ASM_CONST(0xc000000000000000)
#define SLB_VSID_B_256M ASM_CONST(0x0000000000000000)
#define SLB_VSID_B_1T ASM_CONST(0x4000000000000000)
#define SLB_VSID_KS ASM_CONST(0x0000000000000800)
#define SLB_VSID_KP ASM_CONST(0x0000000000000400)
#define SLB_VSID_N ASM_CONST(0x0000000000000200)  
#define SLB_VSID_L ASM_CONST(0x0000000000000100)
#define SLB_VSID_C ASM_CONST(0x0000000000000080)  
#define SLB_VSID_LP ASM_CONST(0x0000000000000030)
#define SLB_VSID_LP_00 ASM_CONST(0x0000000000000000)
#define SLB_VSID_LP_01 ASM_CONST(0x0000000000000010)
#define SLB_VSID_LP_10 ASM_CONST(0x0000000000000020)
#define SLB_VSID_LP_11 ASM_CONST(0x0000000000000030)
#define SLB_VSID_LLP (SLB_VSID_L|SLB_VSID_LP)

#define SLB_VSID_KERNEL (SLB_VSID_KP)
#define SLB_VSID_USER (SLB_VSID_KP|SLB_VSID_KS|SLB_VSID_C)

#define SLBIE_C (0x08000000)
#define SLBIE_SSIZE_SHIFT 25

#define HPTES_PER_GROUP 8

#define HPTE_V_SSIZE_SHIFT 62
#define HPTE_V_AVPN_SHIFT 7
#define HPTE_V_AVPN ASM_CONST(0x3fffffffffffff80)
#define HPTE_V_AVPN_VAL(x) (((x) & HPTE_V_AVPN) >> HPTE_V_AVPN_SHIFT)
#define HPTE_V_COMPARE(x,y) (!(((x) ^ (y)) & 0xffffffffffffff80UL))
#define HPTE_V_BOLTED ASM_CONST(0x0000000000000010)
#define HPTE_V_LOCK ASM_CONST(0x0000000000000008)
#define HPTE_V_LARGE ASM_CONST(0x0000000000000004)
#define HPTE_V_SECONDARY ASM_CONST(0x0000000000000002)
#define HPTE_V_VALID ASM_CONST(0x0000000000000001)

#define HPTE_R_PP0 ASM_CONST(0x8000000000000000)
#define HPTE_R_TS ASM_CONST(0x4000000000000000)
#define HPTE_R_KEY_HI ASM_CONST(0x3000000000000000)
#define HPTE_R_RPN_SHIFT 12
#define HPTE_R_RPN ASM_CONST(0x0ffffffffffff000)
#define HPTE_R_PP ASM_CONST(0x0000000000000003)
#define HPTE_R_N ASM_CONST(0x0000000000000004)
#define HPTE_R_G ASM_CONST(0x0000000000000008)
#define HPTE_R_M ASM_CONST(0x0000000000000010)
#define HPTE_R_I ASM_CONST(0x0000000000000020)
#define HPTE_R_W ASM_CONST(0x0000000000000040)
#define HPTE_R_WIMG ASM_CONST(0x0000000000000078)
#define HPTE_R_C ASM_CONST(0x0000000000000080)
#define HPTE_R_R ASM_CONST(0x0000000000000100)
#define HPTE_R_KEY_LO ASM_CONST(0x0000000000000e00)

#define HPTE_V_1TB_SEG ASM_CONST(0x4000000000000000)
#define HPTE_V_VRMA_MASK ASM_CONST(0x4001ffffff000000)

#define PP_RWXX 0  
#define PP_RWRX 1  
#define PP_RWRW 2  
#define PP_RXRX 3  

#ifndef __ASSEMBLY__

struct hash_pte {
 unsigned long v;
 unsigned long r;
};

struct mmu_psize_def
{
 unsigned int shift;
 unsigned int penc;
 unsigned int tlbiel;
 unsigned long avpnm;
 unsigned long sllp;
};

#endif

#define MMU_SEGSIZE_256M 0
#define MMU_SEGSIZE_1T 1

#ifndef __ASSEMBLY__

struct mm_struct;

#endif

#define VSID_MULTIPLIER_256M ASM_CONST(200730139)  
#define VSID_BITS_256M 36
#define VSID_MODULUS_256M ((1UL<<VSID_BITS_256M)-1)

#define VSID_MULTIPLIER_1T ASM_CONST(12538073)  
#define VSID_BITS_1T 24
#define VSID_MODULUS_1T ((1UL<<VSID_BITS_1T)-1)

#define CONTEXT_BITS 19
#define USER_ESID_BITS 16
#define USER_ESID_BITS_1T 4

#define USER_VSID_RANGE (1UL << (USER_ESID_BITS + SID_SHIFT))

#define ASM_VSID_SCRAMBLE(rt, rx, size)   lis rx,VSID_MULTIPLIER_##size@h;   ori rx,rx,VSID_MULTIPLIER_##size@l;   mulld rt,rt,rx;       srdi rx,rt,VSID_BITS_##size;   clrldi rt,rt,(64-VSID_BITS_##size);   add rt,rt,rx;        addi rx,rt,1;   srdi rx,rx,VSID_BITS_##size;     add rt,rt,rx

#ifndef __ASSEMBLY__

struct spinlock;

typedef struct {
 mm_context_id_t id;
 u16 user_psize;

 u16 sllp;
 unsigned long vdso_base;
} mm_context_t;

#define vsid_scramble(protovsid, size)   ({   unsigned long x;   x = (protovsid) * VSID_MULTIPLIER_##size;   x = (x >> VSID_BITS_##size) + (x & VSID_MODULUS_##size);   (x + ((x+1) >> VSID_BITS_##size)) & VSID_MODULUS_##size;   })

#define VSID_SCRAMBLE(pvsid) (((pvsid) * VSID_MULTIPLIER_256M) %   VSID_MODULUS_256M)
#define KERNEL_VSID(ea) VSID_SCRAMBLE(GET_ESID(ea))
#endif
#endif
