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
#ifndef _ASM_POWERPC_TERMIOS_H
#define _ASM_POWERPC_TERMIOS_H

#include <asm/ioctls.h>
#include <asm/termbits.h>

struct winsize {
 unsigned short ws_row;
 unsigned short ws_col;
 unsigned short ws_xpixel;
 unsigned short ws_ypixel;
};

#define NCC 10
struct termio {
 unsigned short c_iflag;
 unsigned short c_oflag;
 unsigned short c_cflag;
 unsigned short c_lflag;
 unsigned char c_line;
 unsigned char c_cc[NCC];
};

#define _VINTR 0
#define _VQUIT 1
#define _VERASE 2
#define _VKILL 3
#define _VEOF 4
#define _VMIN 5
#define _VEOL 6
#define _VTIME 7
#define _VEOL2 8
#define _VSWTC 9

#define N_TTY 0
#define N_SLIP 1
#define N_MOUSE 2
#define N_PPP 3
#define N_STRIP 4
#define N_AX25 5
#define N_X25 6  
#define N_6PACK 7
#define N_MASC 8  
#define N_R3964 9  
#define N_PROFIBUS_FDL 10  
#define N_IRDA 11  
#define N_SMSBLOCK 12  
#define N_HDLC 13  
#define N_SYNC_PPP 14
#define N_HCI 15  

#endif
