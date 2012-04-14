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
#ifndef __PPC_KERNEL_TSI108_H
#define __PPC_KERNEL_TSI108_H

#include <asm/pci-bridge.h>

#define TSI108_REG_SIZE (0x10000)

#define TSI108_HLP_SIZE 0x1000
#define TSI108_PCI_SIZE 0x1000
#define TSI108_CLK_SIZE 0x1000
#define TSI108_PB_SIZE 0x1000
#define TSI108_SD_SIZE 0x1000
#define TSI108_DMA_SIZE 0x1000
#define TSI108_ETH_SIZE 0x1000
#define TSI108_I2C_SIZE 0x400
#define TSI108_MPIC_SIZE 0x400
#define TSI108_UART0_SIZE 0x200
#define TSI108_GPIO_SIZE 0x200
#define TSI108_UART1_SIZE 0x200

#define TSI108_HLP_OFFSET 0x0000
#define TSI108_PCI_OFFSET 0x1000
#define TSI108_CLK_OFFSET 0x2000
#define TSI108_PB_OFFSET 0x3000
#define TSI108_SD_OFFSET 0x4000
#define TSI108_DMA_OFFSET 0x5000
#define TSI108_ETH_OFFSET 0x6000
#define TSI108_I2C_OFFSET 0x7000
#define TSI108_MPIC_OFFSET 0x7400
#define TSI108_UART0_OFFSET 0x7800
#define TSI108_GPIO_OFFSET 0x7A00
#define TSI108_UART1_OFFSET 0x7C00

#define TSI108_PCI_CSR (0x004)
#define TSI108_PCI_IRP_CFG_CTL (0x180)
#define TSI108_PCI_IRP_STAT (0x184)
#define TSI108_PCI_IRP_ENABLE (0x188)
#define TSI108_PCI_IRP_INTAD (0x18C)

#define TSI108_PCI_IRP_STAT_P_INT (0x00400000)
#define TSI108_PCI_IRP_ENABLE_P_INT (0x00400000)

#define TSI108_CG_PWRUP_STATUS (0x234)

#define TSI108_PB_ISR (0x00C)
#define TSI108_PB_ERRCS (0x404)
#define TSI108_PB_AERR (0x408)

#define TSI108_PB_ERRCS_ES (1 << 1)
#define TSI108_PB_ISR_PBS_RD_ERR (1 << 8)

#define TSI108_PCI_CFG_SIZE (0x01000000)

#define TSI108_PHY_MV88E 0  
#define TSI108_PHY_BCM54XX 1  

typedef struct {
 u32 regs;
 u32 phyregs;
 u16 phy;
 u16 irq_num;
 u8 mac_addr[6];
 u16 phy_type;
} hw_info;

#endif
