/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>
#include <sys/regdef.h>
#define __NR_pipe2	4328

    .text
    .globl pipe
    .align 2
    .ent pipe,0

pipe:
    .set noreorder

    .cpload t9
    move a1, zero
    li v0, __NR_pipe2
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
    .end pipe
    .size pipe,.-pipe
