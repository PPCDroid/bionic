/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl unlink
    .type unlink,@function
    .align 4

unlink:
    li  0, __NR_unlink
    sc
    bnslr+
    b   __set_syscall_errno
    .size unlink,.-unlink
