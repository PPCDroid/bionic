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
#ifndef __ASM_PPC_RHEAP_H__
#define __ASM_PPC_RHEAP_H__

#include <linux/list.h>

typedef struct _rh_block {
 struct list_head list;
 unsigned long start;
 int size;
 const char *owner;
} rh_block_t;

typedef struct _rh_info {
 unsigned int alignment;
 int max_blocks;
 int empty_slots;
 rh_block_t *block;
 struct list_head empty_list;
 struct list_head free_list;
 struct list_head taken_list;
 unsigned int flags;
} rh_info_t;

#define RHIF_STATIC_INFO 0x1
#define RHIF_STATIC_BLOCK 0x2

typedef struct _rh_stats {
 unsigned long start;
 int size;
 const char *owner;
} rh_stats_t;

#define RHGS_FREE 0
#define RHGS_TAKEN 1

#endif
