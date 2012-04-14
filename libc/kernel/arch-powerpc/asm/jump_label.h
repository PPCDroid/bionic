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
#ifndef _ASM_POWERPC_JUMP_LABEL_H
#define _ASM_POWERPC_JUMP_LABEL_H

#include <linux/types.h>

#include <asm/feature-fixups.h>

#define JUMP_ENTRY_TYPE stringify_in_c(FTR_ENTRY_LONG)
#define JUMP_LABEL_NOP_SIZE 4

struct jump_entry {
 jump_label_t code;
 jump_label_t target;
 jump_label_t key;
};

#endif
