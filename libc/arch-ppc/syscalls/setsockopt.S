/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl setsockopt
    .type setsockopt,@function
    .align 4

setsockopt:
    /* == SAVE 32 (5 params) == */
    addi 1,1,-32
    stw  3,12(1)
    stw  4,16(1)
    stw  5,20(1)
    stw  6,24(1)
    stw  7,28(1)
    li 3,14
    addi 4,1,12
    li 0, __NR_socketcall
    sc
    addi 1,1,32
    bnslr+
    b  __set_syscall_errno
    .size setsockopt,.-setsockopt
