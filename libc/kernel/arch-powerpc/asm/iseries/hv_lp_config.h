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
#ifndef _ASM_POWERPC_ISERIES_HV_LP_CONFIG_H
#define _ASM_POWERPC_ISERIES_HV_LP_CONFIG_H

#include <asm/iseries/hv_call_sc.h>
#include <asm/iseries/hv_types.h>

enum {
 HvCallCfg_Cur = 0,
 HvCallCfg_Init = 1,
 HvCallCfg_Max = 2,
 HvCallCfg_Min = 3
};

#define HvCallCfgGetSystemPhysicalProcessors HvCallCfg + 6
#define HvCallCfgGetPhysicalProcessors HvCallCfg + 7
#define HvCallCfgGetMsChunks HvCallCfg + 9
#define HvCallCfgGetSharedPoolIndex HvCallCfg + 20
#define HvCallCfgGetSharedProcUnits HvCallCfg + 21
#define HvCallCfgGetNumProcsInSharedPool HvCallCfg + 22
#define HvCallCfgGetVirtualLanIndexMap HvCallCfg + 30
#define HvCallCfgGetHostingLpIndex HvCallCfg + 32

#endif
