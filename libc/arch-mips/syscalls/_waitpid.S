/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>
#include <sys/regdef.h>

    .text
    .globl _waitpid
    .align 2
    .ent _waitpid,0

_waitpid:
    .set noreorder

    .cpload t9
    li v0, __NR_waitpid
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
    .end _waitpid
    .size _waitpid,.-_waitpid
