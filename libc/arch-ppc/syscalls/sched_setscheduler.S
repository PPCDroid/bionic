/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl sched_setscheduler
    .type sched_setscheduler,@function
    .align 4

sched_setscheduler:
    li  0, __NR_sched_setscheduler
    sc
    bnslr+
    b   __set_syscall_errno
    .size sched_setscheduler,.-sched_setscheduler
