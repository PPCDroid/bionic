/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _ASM_POWERPC_POSIX_TYPES_H
#define _ASM_POWERPC_POSIX_TYPES_H

typedef unsigned long __kernel_ino_t;
typedef unsigned int __kernel_mode_t;
typedef long __kernel_off_t;
typedef int __kernel_pid_t;
typedef unsigned int __kernel_uid_t;
typedef unsigned int __kernel_gid_t;
typedef long __kernel_ptrdiff_t;
typedef long __kernel_time_t;
typedef long __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef long __kernel_suseconds_t;
typedef int __kernel_daddr_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;
typedef unsigned int __kernel_old_uid_t;
typedef unsigned int __kernel_old_gid_t;

#ifdef __powerpc64__
typedef unsigned long __kernel_nlink_t;
typedef int __kernel_ipc_pid_t;
typedef unsigned long __kernel_size_t;
typedef long __kernel_ssize_t;
typedef unsigned long __kernel_old_dev_t;
#else
typedef unsigned short __kernel_nlink_t;
typedef short __kernel_ipc_pid_t;
typedef unsigned int __kernel_size_t;
typedef int __kernel_ssize_t;
typedef unsigned int __kernel_old_dev_t;
#endif

#ifdef __powerpc64__
typedef long long __kernel_loff_t;
#else
#ifdef __GNUC__
typedef long long __kernel_loff_t;
#endif
#endif

typedef struct {
 int val[2];
} __kernel_fsid_t;

#define __FD_SET(d, set) ((set)->fds_bits[__FDELT(d)] |= __FDMASK(d))
#define __FD_CLR(d, set) ((set)->fds_bits[__FDELT(d)] &= ~__FDMASK(d))
#define __FD_ISSET(d, set) (((set)->fds_bits[__FDELT(d)] & __FDMASK(d)) != 0)
#define __FD_ZERO(set)   ((void) memset ((void *) (set), 0, sizeof (__kernel_fd_set)))

#ifdef __GNUC__

#endif
#endif
