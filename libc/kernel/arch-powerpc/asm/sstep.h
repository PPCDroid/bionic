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
struct pt_regs;

#define IS_MTMSRD(instr) (((instr) & 0xfc0007be) == 0x7c000124)
#define IS_RFID(instr) (((instr) & 0xfc0007fe) == 0x4c000024)
#define IS_RFI(instr) (((instr) & 0xfc0007fe) == 0x4c000064)

