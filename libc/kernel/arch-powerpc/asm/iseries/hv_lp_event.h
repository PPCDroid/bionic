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
#ifndef _ASM_POWERPC_ISERIES_HV_LP_EVENT_H
#define _ASM_POWERPC_ISERIES_HV_LP_EVENT_H

#include <asm/types.h>
#include <asm/ptrace.h>
#include <asm/iseries/hv_types.h>
#include <asm/iseries/hv_call_event.h>

struct HvLpEvent {
 u8 flags;
 u8 xType;
 u16 xSubtype;
 u8 xSourceLp;
 u8 xTargetLp;
 u8 xSizeMinus1;
 u8 xRc;
 u16 xSourceInstanceId;
 u16 xTargetInstanceId;
 union {
 u32 xSubtypeData;
 u16 xSubtypeDataShort[2];
 u8 xSubtypeDataChar[4];
 } x;

 u64 xCorrelationToken;
};

typedef void (*LpEventHandler)(struct HvLpEvent *);

#define HvLpEvent_Type_Hypervisor 0
#define HvLpEvent_Type_MachineFac 1
#define HvLpEvent_Type_SessionMgr 2
#define HvLpEvent_Type_SpdIo 3
#define HvLpEvent_Type_VirtualBus 4
#define HvLpEvent_Type_PciIo 5
#define HvLpEvent_Type_RioIo 6
#define HvLpEvent_Type_VirtualLan 7
#define HvLpEvent_Type_VirtualIo 8
#define HvLpEvent_Type_NumTypes 9

#define HvLpEvent_Rc_Good 0
#define HvLpEvent_Rc_BufferNotAvailable 1
#define HvLpEvent_Rc_Cancelled 2
#define HvLpEvent_Rc_GenericError 3
#define HvLpEvent_Rc_InvalidAddress 4
#define HvLpEvent_Rc_InvalidPartition 5
#define HvLpEvent_Rc_InvalidSize 6
#define HvLpEvent_Rc_InvalidSubtype 7
#define HvLpEvent_Rc_InvalidSubtypeData 8
#define HvLpEvent_Rc_InvalidType 9
#define HvLpEvent_Rc_PartitionDead 10
#define HvLpEvent_Rc_PathClosed 11
#define HvLpEvent_Rc_SubtypeError 12

#define HvLpEvent_Function_Ack 0
#define HvLpEvent_Function_Int 1

#define HvLpEvent_AckInd_NoAck 0
#define HvLpEvent_AckInd_DoAck 1

#define HvLpEvent_AckType_ImmediateAck 0
#define HvLpEvent_AckType_DeferredAck 1

#define HV_LP_EVENT_INT 0x01
#define HV_LP_EVENT_DO_ACK 0x02
#define HV_LP_EVENT_DEFERRED_ACK 0x04
#define HV_LP_EVENT_VALID 0x80

#define HvLpDma_Direction_LocalToRemote 0
#define HvLpDma_Direction_RemoteToLocal 1

#define HvLpDma_AddressType_TceIndex 0
#define HvLpDma_AddressType_RealAddress 1

#define HvLpDma_Rc_Good 0
#define HvLpDma_Rc_Error 1
#define HvLpDma_Rc_PartitionDead 2
#define HvLpDma_Rc_PathClosed 3
#define HvLpDma_Rc_InvalidAddress 4
#define HvLpDma_Rc_InvalidLength 5

#endif
