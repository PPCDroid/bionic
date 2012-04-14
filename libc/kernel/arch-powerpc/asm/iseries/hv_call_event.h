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
#ifndef _ASM_POWERPC_ISERIES_HV_CALL_EVENT_H
#define _ASM_POWERPC_ISERIES_HV_CALL_EVENT_H

#include <linux/types.h>
#include <linux/dma-mapping.h>

#include <asm/iseries/hv_call_sc.h>
#include <asm/iseries/hv_types.h>
#include <asm/abs_addr.h>

struct HvLpEvent;

typedef u8 HvLpEvent_Type;
typedef u8 HvLpEvent_AckInd;
typedef u8 HvLpEvent_AckType;

typedef u8 HvLpDma_Direction;
typedef u8 HvLpDma_AddressType;

typedef u64 HvLpEvent_Rc;
typedef u64 HvLpDma_Rc;

#define HvCallEventAckLpEvent HvCallEvent + 0
#define HvCallEventCancelLpEvent HvCallEvent + 1
#define HvCallEventCloseLpEventPath HvCallEvent + 2
#define HvCallEventDmaBufList HvCallEvent + 3
#define HvCallEventDmaSingle HvCallEvent + 4
#define HvCallEventDmaToSp HvCallEvent + 5
#define HvCallEventGetOverflowLpEvents HvCallEvent + 6
#define HvCallEventGetSourceLpInstanceId HvCallEvent + 7
#define HvCallEventGetTargetLpInstanceId HvCallEvent + 8
#define HvCallEventOpenLpEventPath HvCallEvent + 9
#define HvCallEventSetLpEventStack HvCallEvent + 10
#define HvCallEventSignalLpEvent HvCallEvent + 11
#define HvCallEventSignalLpEventParms HvCallEvent + 12
#define HvCallEventSetInterLpQueueIndex HvCallEvent + 13
#define HvCallEventSetLpEventQueueInterruptProc HvCallEvent + 14
#define HvCallEventRouter15 HvCallEvent + 15

#endif
