/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl writev
    .type writev,@function
    .align 4

writev:
    li  0, __NR_writev
    sc
    bnslr+
    b   __set_syscall_errno
    .size writev,.-writev
