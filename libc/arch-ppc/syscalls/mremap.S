/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl mremap
    .type mremap,@function
    .align 4

mremap:
    li  0, __NR_mremap
    sc
    bnslr+
    b   __set_syscall_errno
    .size mremap,.-mremap
