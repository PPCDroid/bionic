/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl _waitpid
    .type _waitpid,@function
    .align 4

_waitpid:
    li  0, __NR_waitpid
    sc
    bnslr+
    b   __set_syscall_errno
    .size _waitpid,.-_waitpid
