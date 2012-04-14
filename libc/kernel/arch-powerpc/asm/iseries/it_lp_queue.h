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
#ifndef _ASM_POWERPC_ISERIES_IT_LP_QUEUE_H
#define _ASM_POWERPC_ISERIES_IT_LP_QUEUE_H

#include <asm/types.h>
#include <asm/ptrace.h>

#define IT_LP_MAX_QUEUES 8

#define IT_LP_NOT_USED 0  
#define IT_LP_DEDICATED_IO 1  
#define IT_LP_DEDICATED_LP 2  
#define IT_LP_SHARED 3  

#define IT_LP_EVENT_STACK_SIZE 4096
#define IT_LP_EVENT_MAX_SIZE 256
#define IT_LP_EVENT_ALIGN 64

struct hvlpevent_queue {

 u8 hq_overflow_pending;
 u8 hq_status;
 u16 hq_proc_index;
 u8 hq_reserved1[12];
 char *hq_current_event;
 char *hq_last_event;
 char *hq_event_stack;
 u8 hq_index;
 u8 hq_reserved2[3];
 spinlock_t hq_lock;
};

#endif
