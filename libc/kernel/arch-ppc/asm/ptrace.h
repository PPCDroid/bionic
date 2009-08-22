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
#ifndef _ASM_POWERPC_PTRACE_H
#define _ASM_POWERPC_PTRACE_H

#ifndef __ASSEMBLY__

struct pt_regs {
 unsigned long gpr[32];
 unsigned long nip;
 unsigned long msr;
 unsigned long orig_gpr3;
 unsigned long ctr;
 unsigned long link;
 unsigned long xer;
 unsigned long ccr;
#ifdef __powerpc64__
 unsigned long softe;
#else
 unsigned long mq;

#endif
 unsigned long trap;

 unsigned long dar;
 unsigned long dsisr;
 unsigned long result;
};

#endif

#define PT_R0 0
#define PT_R1 1
#define PT_R2 2
#define PT_R3 3
#define PT_R4 4
#define PT_R5 5
#define PT_R6 6
#define PT_R7 7
#define PT_R8 8
#define PT_R9 9
#define PT_R10 10
#define PT_R11 11
#define PT_R12 12
#define PT_R13 13
#define PT_R14 14
#define PT_R15 15
#define PT_R16 16
#define PT_R17 17
#define PT_R18 18
#define PT_R19 19
#define PT_R20 20
#define PT_R21 21
#define PT_R22 22
#define PT_R23 23
#define PT_R24 24
#define PT_R25 25
#define PT_R26 26
#define PT_R27 27
#define PT_R28 28
#define PT_R29 29
#define PT_R30 30
#define PT_R31 31

#define PT_NIP 32
#define PT_MSR 33
#define PT_ORIG_R3 34
#define PT_CTR 35
#define PT_LNK 36
#define PT_XER 37
#define PT_CCR 38
#ifndef __powerpc64__
#define PT_MQ 39
#else
#define PT_SOFTE 39
#endif
#define PT_TRAP 40
#define PT_DAR 41
#define PT_DSISR 42
#define PT_RESULT 43
#define PT_REGS_COUNT 44

#define PT_FPR0 48  

#ifndef __powerpc64__

#define PT_FPR31 (PT_FPR0 + 2*31)
#define PT_FPSCR (PT_FPR0 + 2*32 + 1)

#else

#define PT_FPSCR (PT_FPR0 + 32)  

#define PT_VR0 82  
#define PT_VSCR (PT_VR0 + 32*2 + 1)
#define PT_VRSAVE (PT_VR0 + 33*2)

#define PT_VSR0 150  
#define PT_VSR31 (PT_VSR0 + 2*31)
#endif

#define PTRACE_GETVRREGS 18
#define PTRACE_SETVRREGS 19

#define PTRACE_GETEVRREGS 20
#define PTRACE_SETEVRREGS 21

#define PTRACE_GETVSRREGS 27
#define PTRACE_SETVSRREGS 28

#define PTRACE_GET_DEBUGREG 25
#define PTRACE_SET_DEBUGREG 26

#define PTRACE_GETREGS 12
#define PTRACE_SETREGS 13
#define PTRACE_GETFPREGS 14
#define PTRACE_SETFPREGS 15
#define PTRACE_GETREGS64 22
#define PTRACE_SETREGS64 23

#define PPC_PTRACE_GETREGS 0x99  
#define PPC_PTRACE_SETREGS 0x98  
#define PPC_PTRACE_GETFPREGS 0x97  
#define PPC_PTRACE_SETFPREGS 0x96  

#define PPC_PTRACE_PEEKTEXT_3264 0x95
#define PPC_PTRACE_PEEKDATA_3264 0x94
#define PPC_PTRACE_POKETEXT_3264 0x93
#define PPC_PTRACE_POKEDATA_3264 0x92
#define PPC_PTRACE_PEEKUSR_3264 0x91
#define PPC_PTRACE_POKEUSR_3264 0x90

#endif
