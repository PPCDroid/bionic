/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl inotify_rm_watch
    .type inotify_rm_watch,@function
    .align 4

inotify_rm_watch:
    li  0, __NR_inotify_rm_watch
    sc
    bnslr+
    b   __set_syscall_errno
    .size inotify_rm_watch,.-inotify_rm_watch
