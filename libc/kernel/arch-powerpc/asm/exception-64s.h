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
#ifndef _ASM_POWERPC_EXCEPTION_H
#define _ASM_POWERPC_EXCEPTION_H

#define EX_R9 0
#define EX_R10 8
#define EX_R11 16
#define EX_R12 24
#define EX_R13 32
#define EX_SRR0 40
#define EX_DAR 48
#define EX_DSISR 56
#define EX_CCR 60
#define EX_R3 64
#define EX_LR 72
#define EX_CFAR 80

#define LOAD_HANDLER(reg, label)   addi reg,reg,(label)-_stext;  

#define EXC_HV H
#define EXC_STD

#define __EXCEPTION_PROLOG_1(area, extra, vec)   GET_PACA(r13);   std r9,area+EX_R9(r13);     std r10,area+EX_R10(r13);   BEGIN_FTR_SECTION_NESTED(66);   mfspr r10,SPRN_CFAR;   std r10,area+EX_CFAR(r13);   END_FTR_SECTION_NESTED(CPU_FTR_CFAR, CPU_FTR_CFAR, 66);   mfcr r9;   extra(vec);   std r11,area+EX_R11(r13);   std r12,area+EX_R12(r13);   GET_SCRATCH0(r10);   std r10,area+EX_R13(r13)
#define EXCEPTION_PROLOG_1(area, extra, vec)   __EXCEPTION_PROLOG_1(area, extra, vec)

#define __EXCEPTION_PROLOG_PSERIES_1(label, h)   ld r12,PACAKBASE(r13);     ld r10,PACAKMSR(r13);     mfspr r11,SPRN_##h##SRR0;     LOAD_HANDLER(r12,label)   mtspr SPRN_##h##SRR0,r12;   mfspr r12,SPRN_##h##SRR1;     mtspr SPRN_##h##SRR1,r10;   h##rfid;   b .  
#define EXCEPTION_PROLOG_PSERIES_1(label, h)   __EXCEPTION_PROLOG_PSERIES_1(label, h)

#define EXCEPTION_PROLOG_PSERIES(area, label, h, extra, vec)   EXCEPTION_PROLOG_1(area, extra, vec);   EXCEPTION_PROLOG_PSERIES_1(label, h);

#define __KVMTEST(n)   lbz r10,HSTATE_IN_GUEST(r13);   cmpwi r10,0;   bne do_kvm_##n

#define __KVM_HANDLER(area, h, n)  do_kvm_##n:   ld r10,area+EX_R10(r13);   stw r9,HSTATE_SCRATCH1(r13);   ld r9,area+EX_R9(r13);   std r12,HSTATE_SCRATCH0(r13);   li r12,n;   b kvmppc_interrupt

#define __KVM_HANDLER_SKIP(area, h, n)  do_kvm_##n:   cmpwi r10,KVM_GUEST_MODE_SKIP;   ld r10,area+EX_R10(r13);   beq 89f;   stw r9,HSTATE_SCRATCH1(r13);   ld r9,area+EX_R9(r13);   std r12,HSTATE_SCRATCH0(r13);   li r12,n;   b kvmppc_interrupt;  89: mtocrf 0x80,r9;   ld r9,area+EX_R9(r13);   b kvmppc_skip_##h##interrupt

#define KVMTEST(n)
#define KVM_HANDLER(area, h, n)
#define KVM_HANDLER_SKIP(area, h, n)

#define KVMTEST_PR(n)
#define KVM_HANDLER_PR(area, h, n)
#define KVM_HANDLER_PR_SKIP(area, h, n)

#define NOTEST(n)

#define EXCEPTION_PROLOG_COMMON(n, area)   andi. r10,r12,MSR_PR;     mr r10,r1;     subi r1,r1,INT_FRAME_SIZE;     beq- 1f;   ld r1,PACAKSAVE(r13);    1: cmpdi cr1,r1,0;     blt+ cr1,3f;     li r1,(n);     sth r1,PACA_TRAP_SAVE(r13);   std r3,area+EX_R3(r13);   addi r3,r13,area;     b bad_stack;  3: std r9,_CCR(r1);     std r11,_NIP(r1);     std r12,_MSR(r1);     std r10,0(r1);     std r0,GPR0(r1);     std r10,GPR1(r1);     ACCOUNT_CPU_USER_ENTRY(r9, r10);   std r2,GPR2(r1);     SAVE_4GPRS(3, r1);     SAVE_2GPRS(7, r1);     ld r9,area+EX_R9(r13);     ld r10,area+EX_R10(r13);   std r9,GPR9(r1);   std r10,GPR10(r1);   ld r9,area+EX_R11(r13);     ld r10,area+EX_R12(r13);   ld r11,area+EX_R13(r13);   std r9,GPR11(r1);   std r10,GPR12(r1);   std r11,GPR13(r1);   BEGIN_FTR_SECTION_NESTED(66);   ld r10,area+EX_CFAR(r13);   std r10,ORIG_GPR3(r1);   END_FTR_SECTION_NESTED(CPU_FTR_CFAR, CPU_FTR_CFAR, 66);   ld r2,PACATOC(r13);     mflr r9;     std r9,_LINK(r1);   mfctr r10;     std r10,_CTR(r1);   lbz r10,PACASOFTIRQEN(r13);   mfspr r11,SPRN_XER;     std r10,SOFTE(r1);   std r11,_XER(r1);   li r9,(n)+1;   std r9,_TRAP(r1);     li r10,0;   ld r11,exception_marker@toc(r2);   std r10,RESULT(r1);     std r11,STACK_FRAME_OVERHEAD-16(r1);     ACCOUNT_STOLEN_TIME

#define STD_EXCEPTION_PSERIES(loc, vec, label)   . = loc;   .globl label##_pSeries;  label##_pSeries:   HMT_MEDIUM;   SET_SCRATCH0(r13);     EXCEPTION_PROLOG_PSERIES(PACA_EXGEN, label##_common,   EXC_STD, KVMTEST_PR, vec)

#define STD_EXCEPTION_HV(loc, vec, label)   . = loc;   .globl label##_hv;  label##_hv:   HMT_MEDIUM;   SET_SCRATCH0(r13);     EXCEPTION_PROLOG_PSERIES(PACA_EXGEN, label##_common,   EXC_HV, KVMTEST, vec)

#define __SOFTEN_TEST(h)   lbz r10,PACASOFTIRQEN(r13);   cmpwi r10,0;   beq masked_##h##interrupt
#define _SOFTEN_TEST(h) __SOFTEN_TEST(h)

#define SOFTEN_TEST_PR(vec)   KVMTEST_PR(vec);   _SOFTEN_TEST(EXC_STD)

#define SOFTEN_TEST_HV(vec)   KVMTEST(vec);   _SOFTEN_TEST(EXC_HV)

#define SOFTEN_TEST_HV_201(vec)   KVMTEST(vec);   _SOFTEN_TEST(EXC_STD)

#define __MASKABLE_EXCEPTION_PSERIES(vec, label, h, extra)   HMT_MEDIUM;   SET_SCRATCH0(r13);     __EXCEPTION_PROLOG_1(PACA_EXGEN, extra, vec);   EXCEPTION_PROLOG_PSERIES_1(label##_common, h);
#define _MASKABLE_EXCEPTION_PSERIES(vec, label, h, extra)   __MASKABLE_EXCEPTION_PSERIES(vec, label, h, extra)

#define MASKABLE_EXCEPTION_PSERIES(loc, vec, label)   . = loc;   .globl label##_pSeries;  label##_pSeries:   _MASKABLE_EXCEPTION_PSERIES(vec, label,   EXC_STD, SOFTEN_TEST_PR)

#define MASKABLE_EXCEPTION_HV(loc, vec, label)   . = loc;   .globl label##_hv;  label##_hv:   _MASKABLE_EXCEPTION_PSERIES(vec, label,   EXC_HV, SOFTEN_TEST_HV)

#define DISABLE_INTS   li r11,0;   stb r11,PACASOFTIRQEN(r13);   stb r11,PACAHARDIRQEN(r13);   TRACE_DISABLE_INTS

#define ENABLE_INTS   ld r12,_MSR(r1);   mfmsr r11;   rlwimi r11,r12,0,MSR_EE;   mtmsrd r11,1

#define STD_EXCEPTION_COMMON(trap, label, hdlr)   .align 7;   .globl label##_common;  label##_common:   EXCEPTION_PROLOG_COMMON(trap, PACA_EXGEN);   DISABLE_INTS;   bl .save_nvgprs;   addi r3,r1,STACK_FRAME_OVERHEAD;   bl hdlr;   b .ret_from_except

#define STD_EXCEPTION_COMMON_IDLE(trap, label, hdlr)   .align 7;   .globl label##_common;  label##_common:   EXCEPTION_PROLOG_COMMON(trap, PACA_EXGEN);   FINISH_NAP;   DISABLE_INTS;   bl .save_nvgprs;   addi r3,r1,STACK_FRAME_OVERHEAD;   bl hdlr;   b .ret_from_except

#define STD_EXCEPTION_COMMON_LITE(trap, label, hdlr)   .align 7;   .globl label##_common;  label##_common:   EXCEPTION_PROLOG_COMMON(trap, PACA_EXGEN);   FINISH_NAP;   DISABLE_INTS;  BEGIN_FTR_SECTION   bl .ppc64_runlatch_on;  END_FTR_SECTION_IFSET(CPU_FTR_CTRL)   addi r3,r1,STACK_FRAME_OVERHEAD;   bl hdlr;   b .ret_from_except_lite

#define FINISH_NAP

#endif
