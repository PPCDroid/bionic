/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>
#include <sys/regdef.h>

    .text
    .globl setrlimit
    .align 2
    .ent setrlimit,0

setrlimit:
    .set noreorder

    .cpload t9
    li v0, __NR_setrlimit
    syscall
    .set reorder
    bne a3, zero, err
    nop
    j ra
    nop
err:
    subu a0, zero, v0
#ifdef __PIC__
    la t9, __set_syscall_errno
    jr t9
#else
    j       __set_syscall_errno
#endif
    nop
    .end setrlimit
    .size setrlimit,.-setrlimit
