/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl readlink
    .type readlink,@function
    .align 4

readlink:
    li  0, __NR_readlink
    sc
    bnslr+
    b   __set_syscall_errno
    .size readlink,.-readlink
