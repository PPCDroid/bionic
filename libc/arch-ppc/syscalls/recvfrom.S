/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl recvfrom
    .type recvfrom,@function
    .align 4

recvfrom:
    /* == SAVE 32 (6 params) == */
    addi 1,1,-32
    stw  3,8(1)
    stw  4,12(1)
    stw  5,16(1)
    stw  6,20(1)
    stw  7,24(1)
    stw  8,28(1)
    li 3,12
    addi 4,1,8
    li 0, __NR_socketcall
    sc
    addi 1,1,32
    bnslr+
    b  __set_syscall_errno
    .size recvfrom,.-recvfrom
