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
#ifndef _ASM_POWERPC_PROCESSOR_H
#define _ASM_POWERPC_PROCESSOR_H

#include <asm/reg.h>

#define TS_FPRWIDTH 1

#ifndef __ASSEMBLY__
#include <linux/compiler.h>
#include <linux/cache.h>
#include <asm/ptrace.h>
#include <asm/types.h>

#define _PREP_Motorola 0x01  
#define _PREP_Firm 0x02  
#define _PREP_IBM 0x00  
#define _PREP_Bull 0x03  

#define _CHRP_Motorola 0x04  
#define _CHRP_IBM 0x05  
#define _CHRP_Pegasos 0x06  
#define _CHRP_briq 0x07  

#define current_text_addr() ({ __label__ _l; _l: &&_l;})

#define HMT_very_low() asm volatile("or 31,31,31   # very low priority")
#define HMT_low() asm volatile("or 1,1,1	     # low priority")
#define HMT_medium_low() asm volatile("or 6,6,6      # medium low priority")
#define HMT_medium() asm volatile("or 2,2,2	     # medium priority")
#define HMT_medium_high() asm volatile("or 5,5,5      # medium high priority")
#define HMT_high() asm volatile("or 3,3,3	     # high priority")

#endif
#endif
