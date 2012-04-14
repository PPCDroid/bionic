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
#ifndef _ASM_POWERPC_ISERIES_HV_CALL_XM_H
#define _ASM_POWERPC_ISERIES_HV_CALL_XM_H

#include <asm/iseries/hv_call_sc.h>
#include <asm/iseries/hv_types.h>

#define HvCallXmGetTceTableParms HvCallXm + 0
#define HvCallXmTestBus HvCallXm + 1
#define HvCallXmConnectBusUnit HvCallXm + 2
#define HvCallXmLoadTod HvCallXm + 8
#define HvCallXmTestBusUnit HvCallXm + 9
#define HvCallXmSetTce HvCallXm + 11
#define HvCallXmSetTces HvCallXm + 13

#endif
