# auto-generated by gensyscalls.py, do not touch
syscall_src := 
syscall_src += arch-powerpc/syscalls/_exit.S
syscall_src += arch-powerpc/syscalls/_exit_thread.S
syscall_src += arch-powerpc/syscalls/__fork.S
syscall_src += arch-powerpc/syscalls/_waitpid.S
syscall_src += arch-powerpc/syscalls/__waitid.S
syscall_src += arch-powerpc/syscalls/__sys_clone.S
syscall_src += arch-powerpc/syscalls/execve.S
syscall_src += arch-powerpc/syscalls/__setuid.S
syscall_src += arch-powerpc/syscalls/getuid.S
syscall_src += arch-powerpc/syscalls/getgid.S
syscall_src += arch-powerpc/syscalls/geteuid.S
syscall_src += arch-powerpc/syscalls/getegid.S
syscall_src += arch-powerpc/syscalls/getresuid.S
syscall_src += arch-powerpc/syscalls/getresgid.S
syscall_src += arch-powerpc/syscalls/gettid.S
syscall_src += arch-powerpc/syscalls/getgroups.S
syscall_src += arch-powerpc/syscalls/getpgid.S
syscall_src += arch-powerpc/syscalls/getppid.S
syscall_src += arch-powerpc/syscalls/setsid.S
syscall_src += arch-powerpc/syscalls/setgid.S
syscall_src += arch-powerpc/syscalls/__setreuid.S
syscall_src += arch-powerpc/syscalls/__setresuid.S
syscall_src += arch-powerpc/syscalls/setresgid.S
syscall_src += arch-powerpc/syscalls/__brk.S
syscall_src += arch-powerpc/syscalls/kill.S
syscall_src += arch-powerpc/syscalls/tkill.S
syscall_src += arch-powerpc/syscalls/__ptrace.S
syscall_src += arch-powerpc/syscalls/__getpriority.S
syscall_src += arch-powerpc/syscalls/setpriority.S
syscall_src += arch-powerpc/syscalls/setrlimit.S
syscall_src += arch-powerpc/syscalls/getrlimit.S
syscall_src += arch-powerpc/syscalls/getrusage.S
syscall_src += arch-powerpc/syscalls/setgroups.S
syscall_src += arch-powerpc/syscalls/setpgid.S
syscall_src += arch-powerpc/syscalls/vfork.S
syscall_src += arch-powerpc/syscalls/setregid.S
syscall_src += arch-powerpc/syscalls/chroot.S
syscall_src += arch-powerpc/syscalls/prctl.S
syscall_src += arch-powerpc/syscalls/capget.S
syscall_src += arch-powerpc/syscalls/capset.S
syscall_src += arch-powerpc/syscalls/sigaltstack.S
syscall_src += arch-powerpc/syscalls/acct.S
syscall_src += arch-powerpc/syscalls/read.S
syscall_src += arch-powerpc/syscalls/write.S
syscall_src += arch-powerpc/syscalls/__pread64.S
syscall_src += arch-powerpc/syscalls/__pwrite64.S
syscall_src += arch-powerpc/syscalls/__open.S
syscall_src += arch-powerpc/syscalls/__openat.S
syscall_src += arch-powerpc/syscalls/close.S
syscall_src += arch-powerpc/syscalls/lseek.S
syscall_src += arch-powerpc/syscalls/__llseek.S
syscall_src += arch-powerpc/syscalls/getpid.S
syscall_src += arch-powerpc/syscalls/__mmap2.S
syscall_src += arch-powerpc/syscalls/munmap.S
syscall_src += arch-powerpc/syscalls/mremap.S
syscall_src += arch-powerpc/syscalls/msync.S
syscall_src += arch-powerpc/syscalls/mprotect.S
syscall_src += arch-powerpc/syscalls/madvise.S
syscall_src += arch-powerpc/syscalls/mlock.S
syscall_src += arch-powerpc/syscalls/munlock.S
syscall_src += arch-powerpc/syscalls/mincore.S
syscall_src += arch-powerpc/syscalls/__ioctl.S
syscall_src += arch-powerpc/syscalls/readv.S
syscall_src += arch-powerpc/syscalls/writev.S
syscall_src += arch-powerpc/syscalls/__fcntl.S
syscall_src += arch-powerpc/syscalls/flock.S
syscall_src += arch-powerpc/syscalls/fchmod.S
syscall_src += arch-powerpc/syscalls/dup.S
syscall_src += arch-powerpc/syscalls/pipe.S
syscall_src += arch-powerpc/syscalls/pipe2.S
syscall_src += arch-powerpc/syscalls/dup2.S
syscall_src += arch-powerpc/syscalls/select.S
syscall_src += arch-powerpc/syscalls/ftruncate.S
syscall_src += arch-powerpc/syscalls/getdents.S
syscall_src += arch-powerpc/syscalls/fsync.S
syscall_src += arch-powerpc/syscalls/fdatasync.S
syscall_src += arch-powerpc/syscalls/fchown.S
syscall_src += arch-powerpc/syscalls/sync.S
syscall_src += arch-powerpc/syscalls/__fcntl64.S
syscall_src += arch-powerpc/syscalls/__fstatfs64.S
syscall_src += arch-powerpc/syscalls/sendfile.S
syscall_src += arch-powerpc/syscalls/fstatat.S
syscall_src += arch-powerpc/syscalls/mkdirat.S
syscall_src += arch-powerpc/syscalls/fchownat.S
syscall_src += arch-powerpc/syscalls/fchmodat.S
syscall_src += arch-powerpc/syscalls/renameat.S
syscall_src += arch-powerpc/syscalls/link.S
syscall_src += arch-powerpc/syscalls/unlink.S
syscall_src += arch-powerpc/syscalls/unlinkat.S
syscall_src += arch-powerpc/syscalls/chdir.S
syscall_src += arch-powerpc/syscalls/mknod.S
syscall_src += arch-powerpc/syscalls/chmod.S
syscall_src += arch-powerpc/syscalls/chown.S
syscall_src += arch-powerpc/syscalls/lchown.S
syscall_src += arch-powerpc/syscalls/mount.S
syscall_src += arch-powerpc/syscalls/umount2.S
syscall_src += arch-powerpc/syscalls/fstat.S
syscall_src += arch-powerpc/syscalls/stat.S
syscall_src += arch-powerpc/syscalls/lstat.S
syscall_src += arch-powerpc/syscalls/mkdir.S
syscall_src += arch-powerpc/syscalls/readlink.S
syscall_src += arch-powerpc/syscalls/rmdir.S
syscall_src += arch-powerpc/syscalls/rename.S
syscall_src += arch-powerpc/syscalls/__getcwd.S
syscall_src += arch-powerpc/syscalls/access.S
syscall_src += arch-powerpc/syscalls/symlink.S
syscall_src += arch-powerpc/syscalls/fchdir.S
syscall_src += arch-powerpc/syscalls/truncate.S
syscall_src += arch-powerpc/syscalls/__statfs64.S
syscall_src += arch-powerpc/syscalls/pause.S
syscall_src += arch-powerpc/syscalls/gettimeofday.S
syscall_src += arch-powerpc/syscalls/settimeofday.S
syscall_src += arch-powerpc/syscalls/times.S
syscall_src += arch-powerpc/syscalls/nanosleep.S
syscall_src += arch-powerpc/syscalls/clock_gettime.S
syscall_src += arch-powerpc/syscalls/clock_settime.S
syscall_src += arch-powerpc/syscalls/clock_getres.S
syscall_src += arch-powerpc/syscalls/clock_nanosleep.S
syscall_src += arch-powerpc/syscalls/getitimer.S
syscall_src += arch-powerpc/syscalls/setitimer.S
syscall_src += arch-powerpc/syscalls/__timer_create.S
syscall_src += arch-powerpc/syscalls/__timer_settime.S
syscall_src += arch-powerpc/syscalls/__timer_gettime.S
syscall_src += arch-powerpc/syscalls/__timer_getoverrun.S
syscall_src += arch-powerpc/syscalls/__timer_delete.S
syscall_src += arch-powerpc/syscalls/utimes.S
syscall_src += arch-powerpc/syscalls/sigaction.S
syscall_src += arch-powerpc/syscalls/sigprocmask.S
syscall_src += arch-powerpc/syscalls/__sigsuspend.S
syscall_src += arch-powerpc/syscalls/__rt_sigaction.S
syscall_src += arch-powerpc/syscalls/__rt_sigprocmask.S
syscall_src += arch-powerpc/syscalls/__rt_sigtimedwait.S
syscall_src += arch-powerpc/syscalls/sigpending.S
syscall_src += arch-powerpc/syscalls/socket.S
syscall_src += arch-powerpc/syscalls/socketpair.S
syscall_src += arch-powerpc/syscalls/bind.S
syscall_src += arch-powerpc/syscalls/connect.S
syscall_src += arch-powerpc/syscalls/listen.S
syscall_src += arch-powerpc/syscalls/accept.S
syscall_src += arch-powerpc/syscalls/getsockname.S
syscall_src += arch-powerpc/syscalls/getpeername.S
syscall_src += arch-powerpc/syscalls/sendto.S
syscall_src += arch-powerpc/syscalls/recvfrom.S
syscall_src += arch-powerpc/syscalls/shutdown.S
syscall_src += arch-powerpc/syscalls/setsockopt.S
syscall_src += arch-powerpc/syscalls/getsockopt.S
syscall_src += arch-powerpc/syscalls/sendmsg.S
syscall_src += arch-powerpc/syscalls/recvmsg.S
syscall_src += arch-powerpc/syscalls/__socketcall.S
syscall_src += arch-powerpc/syscalls/sched_setscheduler.S
syscall_src += arch-powerpc/syscalls/sched_getscheduler.S
syscall_src += arch-powerpc/syscalls/sched_yield.S
syscall_src += arch-powerpc/syscalls/sched_setparam.S
syscall_src += arch-powerpc/syscalls/sched_getparam.S
syscall_src += arch-powerpc/syscalls/sched_get_priority_max.S
syscall_src += arch-powerpc/syscalls/sched_get_priority_min.S
syscall_src += arch-powerpc/syscalls/sched_rr_get_interval.S
syscall_src += arch-powerpc/syscalls/ioprio_set.S
syscall_src += arch-powerpc/syscalls/ioprio_get.S
syscall_src += arch-powerpc/syscalls/uname.S
syscall_src += arch-powerpc/syscalls/__wait4.S
syscall_src += arch-powerpc/syscalls/umask.S
syscall_src += arch-powerpc/syscalls/__reboot.S
syscall_src += arch-powerpc/syscalls/__syslog.S
syscall_src += arch-powerpc/syscalls/init_module.S
syscall_src += arch-powerpc/syscalls/delete_module.S
syscall_src += arch-powerpc/syscalls/klogctl.S
syscall_src += arch-powerpc/syscalls/sysinfo.S
syscall_src += arch-powerpc/syscalls/futex.S
syscall_src += arch-powerpc/syscalls/epoll_create.S
syscall_src += arch-powerpc/syscalls/epoll_ctl.S
syscall_src += arch-powerpc/syscalls/epoll_wait.S
syscall_src += arch-powerpc/syscalls/inotify_init.S
syscall_src += arch-powerpc/syscalls/inotify_add_watch.S
syscall_src += arch-powerpc/syscalls/inotify_rm_watch.S
syscall_src += arch-powerpc/syscalls/poll.S
syscall_src += arch-powerpc/syscalls/eventfd.S
