/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>
#include <sys/regdef.h>

    .text
    .globl epoll_wait
    .align 2
    .ent epoll_wait,0

epoll_wait:
    .set noreorder

    .cpload t9
    li v0, __NR_epoll_wait
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
    .end epoll_wait
    .size epoll_wait,.-epoll_wait
