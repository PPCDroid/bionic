/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl settimeofday
    .type settimeofday,@function
    .align 4

settimeofday:
    li  0, __NR_settimeofday
    sc
    bnslr+
    b   __set_syscall_errno
    .size settimeofday,.-settimeofday
