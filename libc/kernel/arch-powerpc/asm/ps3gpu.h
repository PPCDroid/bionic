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
#ifndef _ASM_POWERPC_PS3GPU_H
#define _ASM_POWERPC_PS3GPU_H

#include <linux/mutex.h>

#include <asm/lv1call.h>

#define L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_SYNC 0x101
#define L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_FLIP 0x102

#define L1GPU_CONTEXT_ATTRIBUTE_FB_SETUP 0x600
#define L1GPU_CONTEXT_ATTRIBUTE_FB_BLIT 0x601
#define L1GPU_CONTEXT_ATTRIBUTE_FB_BLIT_SYNC 0x602
#define L1GPU_CONTEXT_ATTRIBUTE_FB_CLOSE 0x603

#define L1GPU_FB_BLIT_WAIT_FOR_COMPLETION (1ULL << 32)

#define L1GPU_DISPLAY_SYNC_HSYNC 1
#define L1GPU_DISPLAY_SYNC_VSYNC 2

#endif
