/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl gettimeofday
    .type gettimeofday,@function
    .align 4

gettimeofday:
    li  0, __NR_gettimeofday
    sc
    bnslr+
    b   __set_syscall_errno
    .size gettimeofday,.-gettimeofday
