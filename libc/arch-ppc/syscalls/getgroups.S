/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl getgroups
    .type getgroups,@function
    .align 4

getgroups:
    li  0, __NR_getgroups
    sc
    bnslr+
    b   __set_syscall_errno
    .size getgroups,.-getgroups
