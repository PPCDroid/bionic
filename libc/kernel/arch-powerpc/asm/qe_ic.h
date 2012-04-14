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
#ifndef _ASM_POWERPC_QE_IC_H
#define _ASM_POWERPC_QE_IC_H

#include <linux/irq.h>

struct device_node;
struct qe_ic;

#define NUM_OF_QE_IC_GROUPS 6

#define QE_IC_SPREADMODE_GRP_W 0x00000001
#define QE_IC_SPREADMODE_GRP_X 0x00000002
#define QE_IC_SPREADMODE_GRP_Y 0x00000004
#define QE_IC_SPREADMODE_GRP_Z 0x00000008
#define QE_IC_SPREADMODE_GRP_RISCA 0x00000010
#define QE_IC_SPREADMODE_GRP_RISCB 0x00000020

#define QE_IC_LOW_SIGNAL 0x00000100
#define QE_IC_HIGH_SIGNAL 0x00000200

#define QE_IC_GRP_W_PRI0_DEST_SIGNAL_HIGH 0x00001000
#define QE_IC_GRP_W_PRI1_DEST_SIGNAL_HIGH 0x00002000
#define QE_IC_GRP_X_PRI0_DEST_SIGNAL_HIGH 0x00004000
#define QE_IC_GRP_X_PRI1_DEST_SIGNAL_HIGH 0x00008000
#define QE_IC_GRP_Y_PRI0_DEST_SIGNAL_HIGH 0x00010000
#define QE_IC_GRP_Y_PRI1_DEST_SIGNAL_HIGH 0x00020000
#define QE_IC_GRP_Z_PRI0_DEST_SIGNAL_HIGH 0x00040000
#define QE_IC_GRP_Z_PRI1_DEST_SIGNAL_HIGH 0x00080000
#define QE_IC_GRP_RISCA_PRI0_DEST_SIGNAL_HIGH 0x00100000
#define QE_IC_GRP_RISCA_PRI1_DEST_SIGNAL_HIGH 0x00200000
#define QE_IC_GRP_RISCB_PRI0_DEST_SIGNAL_HIGH 0x00400000
#define QE_IC_GRP_RISCB_PRI1_DEST_SIGNAL_HIGH 0x00800000
#define QE_IC_GRP_W_DEST_SIGNAL_SHIFT (12)

enum qe_ic_grp_id {
 QE_IC_GRP_W = 0,
 QE_IC_GRP_X,
 QE_IC_GRP_Y,
 QE_IC_GRP_Z,
 QE_IC_GRP_RISCA,
 QE_IC_GRP_RISCB
};

#endif
