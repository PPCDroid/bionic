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
#ifndef _FSL_HCALLS_H
#define _FSL_HCALLS_H

#include <linux/types.h>
#include <linux/errno.h>
#include <asm/byteorder.h>
#include <asm/epapr_hcalls.h>

#define FH_API_VERSION 1

#define FH_ERR_GET_INFO 1
#define FH_PARTITION_GET_DTPROP 2
#define FH_PARTITION_SET_DTPROP 3
#define FH_PARTITION_RESTART 4
#define FH_PARTITION_GET_STATUS 5
#define FH_PARTITION_START 6
#define FH_PARTITION_STOP 7
#define FH_PARTITION_MEMCPY 8
#define FH_DMA_ENABLE 9
#define FH_DMA_DISABLE 10
#define FH_SEND_NMI 11
#define FH_VMPIC_GET_MSIR 12
#define FH_SYSTEM_RESET 13
#define FH_GET_CORE_STATE 14
#define FH_ENTER_NAP 15
#define FH_EXIT_NAP 16
#define FH_CLAIM_DEVICE 17
#define FH_PARTITION_STOP_DMA 18

#define FH_HCALL_TOKEN(num) _EV_HCALL_TOKEN(EV_FSL_VENDOR_ID, num)

#define FH_DTPROP_MAX_PATHLEN 4096
#define FH_DTPROP_MAX_PROPLEN 32768
#define FH_PARTITION_STOPPED 0
#define FH_PARTITION_RUNNING 1
#define FH_PARTITION_STARTING 2
#define FH_PARTITION_STOPPING 3
#define FH_PARTITION_PAUSING 4
#define FH_PARTITION_PAUSED 5
#define FH_PARTITION_RESUMING 6

#define FH_VCPU_RUN 0
#define FH_VCPU_IDLE 1
#define FH_VCPU_NAP 2
#endif
