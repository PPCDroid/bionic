/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl munlock
    .type munlock,@function
    .align 4

munlock:
    li  0, __NR_munlock
    sc
    bnslr+
    b   __set_syscall_errno
    .size munlock,.-munlock
