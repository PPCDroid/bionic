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
#ifndef _ASM_POWERPC_ISERIES_MF_H
#define _ASM_POWERPC_ISERIES_MF_H

#include <linux/types.h>

#include <asm/iseries/hv_types.h>
#include <asm/iseries/hv_call_event.h>

struct rtc_time;

typedef void (*MFCompleteHandler)(void *clientToken, int returnCode);

#endif
