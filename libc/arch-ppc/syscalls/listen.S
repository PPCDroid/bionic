/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl listen
    .type listen,@function
    .align 4

listen:
    /* == SAVE 16 (2 params) == */
    addi 1,1,-16
    stw  3,8(1)
    stw  4,12(1)
    li 3,4
    addi 4,1,8
    li 0, __NR_socketcall
    sc
    addi 1,1,16
    bnslr+
    b  __set_syscall_errno
    .size listen,.-listen
