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
#ifndef _ASM_POWERPC_SEMBUF_H
#define _ASM_POWERPC_SEMBUF_H

struct semid64_ds {
 struct ipc64_perm sem_perm;
#ifndef __powerpc64__
 unsigned long __unused1;
#endif
 __kernel_time_t sem_otime;
#ifndef __powerpc64__
 unsigned long __unused2;
#endif
 __kernel_time_t sem_ctime;
 unsigned long sem_nsems;
 unsigned long __unused3;
 unsigned long __unused4;
};

#endif
