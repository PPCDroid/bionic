/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl futex
    .type futex,@function
    .align 4

futex:
    li  0, __NR_futex
    sc
    bnslr+
    b   __set_syscall_errno
    .size futex,.-futex
