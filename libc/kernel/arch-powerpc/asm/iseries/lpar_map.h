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
#ifndef _ASM_POWERPC_ISERIES_LPAR_MAP_H
#define _ASM_POWERPC_ISERIES_LPAR_MAP_H

#ifndef __ASSEMBLY__

#include <asm/types.h>

#endif

#define HvEsidsToMap 2
#define HvRangesToMap 1

#define HvPagesToMap 8192

#ifndef __ASSEMBLY__
struct LparMap {
 u64 xNumberEsids;
 u64 xNumberRanges;
 u64 xSegmentTableOffs;
 u64 xRsvd[5];
 struct {
 u64 xKernelEsid;
 u64 xKernelVsid;
 } xEsids[HvEsidsToMap];
 struct {
 u64 xPages;
 u64 xOffset;
 u64 xVPN;
 } xRanges[HvRangesToMap];
};

#endif

#define LPARMAP_PHYS 0x7000

#endif
