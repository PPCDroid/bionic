/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl madvise
    .type madvise,@function
    .align 4

madvise:
    li  0, __NR_madvise
    sc
    bnslr+
    b   __set_syscall_errno
    .size madvise,.-madvise
