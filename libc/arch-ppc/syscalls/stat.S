/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl stat
    .type stat,@function
    .align 4

stat:
    li  0, __NR_stat64
    sc
    bnslr+
    b   __set_syscall_errno
    .size stat,.-stat
