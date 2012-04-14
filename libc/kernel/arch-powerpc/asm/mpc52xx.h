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
#ifndef __ASM_POWERPC_MPC52xx_H__
#define __ASM_POWERPC_MPC52xx_H__

#ifndef __ASSEMBLY__
#include <asm/types.h>
#include <asm/prom.h>
#include <asm/mpc5xxx.h>
#endif

#include <linux/suspend.h>

#define MPC5200_SVR 0x80110010
#define MPC5200_SVR_MASK 0xfffffff0
#define MPC5200B_SVR 0x80110020
#define MPC5200B_SVR_MASK 0xfffffff0

#ifndef __ASSEMBLY__

struct mpc52xx_mmap_ctl {
 u32 mbar;

 u32 cs0_start;
 u32 cs0_stop;
 u32 cs1_start;
 u32 cs1_stop;
 u32 cs2_start;
 u32 cs2_stop;
 u32 cs3_start;
 u32 cs3_stop;
 u32 cs4_start;
 u32 cs4_stop;
 u32 cs5_start;
 u32 cs5_stop;

 u32 sdram0;
 u32 sdram1;

 u32 reserved[4];

 u32 boot_start;
 u32 boot_stop;

 u32 ipbi_ws_ctrl;

 u32 cs6_start;
 u32 cs6_stop;
 u32 cs7_start;
 u32 cs7_stop;
};

struct mpc52xx_sdram {
 u32 mode;
 u32 ctrl;
 u32 config1;
 u32 config2;
};

struct mpc52xx_sdma {
 u32 taskBar;
 u32 currentPointer;
 u32 endPointer;
 u32 variablePointer;

 u8 IntVect1;
 u8 IntVect2;
 u16 PtdCntrl;

 u32 IntPend;
 u32 IntMask;

 u16 tcr[16];

 u8 ipr[32];

 u32 cReqSelect;
 u32 task_size0;
 u32 task_size1;
 u32 MDEDebug;
 u32 ADSDebug;
 u32 Value1;
 u32 Value2;
 u32 Control;
 u32 Status;
 u32 PTDDebug;
};

struct mpc52xx_gpt {
 u32 mode;
 u32 count;
 u32 pwm;
 u32 status;
};

struct mpc52xx_gpio {
 u32 port_config;
 u32 simple_gpioe;
 u32 simple_ode;
 u32 simple_ddr;
 u32 simple_dvo;
 u32 simple_ival;
 u8 outo_gpioe;
 u8 reserved1[3];
 u8 outo_dvo;
 u8 reserved2[3];
 u8 sint_gpioe;
 u8 reserved3[3];
 u8 sint_ode;
 u8 reserved4[3];
 u8 sint_ddr;
 u8 reserved5[3];
 u8 sint_dvo;
 u8 reserved6[3];
 u8 sint_inten;
 u8 reserved7[3];
 u16 sint_itype;
 u16 reserved8;
 u8 gpio_control;
 u8 reserved9[3];
 u8 sint_istat;
 u8 sint_ival;
 u8 bus_errs;
 u8 reserved10;
};

#define MPC52xx_GPIO_PSC_CONFIG_UART_WITHOUT_CD 4
#define MPC52xx_GPIO_PSC_CONFIG_UART_WITH_CD 5
#define MPC52xx_GPIO_PCI_DIS (1<<15)

struct mpc52xx_gpio_wkup {
 u8 wkup_gpioe;
 u8 reserved1[3];
 u8 wkup_ode;
 u8 reserved2[3];
 u8 wkup_ddr;
 u8 reserved3[3];
 u8 wkup_dvo;
 u8 reserved4[3];
 u8 wkup_inten;
 u8 reserved5[3];
 u8 wkup_iinten;
 u8 reserved6[3];
 u16 wkup_itype;
 u8 reserved7[2];
 u8 wkup_maste;
 u8 reserved8[3];
 u8 wkup_ival;
 u8 reserved9[3];
 u8 wkup_istat;
 u8 reserved10[3];
};

struct mpc52xx_xlb {
 u8 reserved[0x40];
 u32 config;
 u32 version;
 u32 status;
 u32 int_enable;
 u32 addr_capture;
 u32 bus_sig_capture;
 u32 addr_timeout;
 u32 data_timeout;
 u32 bus_act_timeout;
 u32 master_pri_enable;
 u32 master_priority;
 u32 base_address;
 u32 snoop_window;
};

#define MPC52xx_XLB_CFG_PLDIS (1 << 31)
#define MPC52xx_XLB_CFG_SNOOP (1 << 15)

struct mpc52xx_cdm {
 u32 jtag_id;
 u32 rstcfg;
 u32 breadcrumb;

 u8 mem_clk_sel;
 u8 xlb_clk_sel;
 u8 ipb_clk_sel;
 u8 pci_clk_sel;

 u8 ext_48mhz_en;
 u8 fd_enable;
 u16 fd_counters;

 u32 clk_enables;

 u8 osc_disable;
 u8 reserved0[3];

 u8 ccs_sleep_enable;
 u8 osc_sleep_enable;
 u8 reserved1;
 u8 ccs_qreq_test;

 u8 soft_reset;
 u8 no_ckstp;
 u8 reserved2[2];

 u8 pll_lock;
 u8 pll_looselock;
 u8 pll_sm_lockwin;
 u8 reserved3;

 u16 reserved4;
 u16 mclken_div_psc1;

 u16 reserved5;
 u16 mclken_div_psc2;

 u16 reserved6;
 u16 mclken_div_psc3;

 u16 reserved7;
 u16 mclken_div_psc6;
};

struct mpc52xx_intr {
 u32 per_mask;
 u32 per_pri1;
 u32 per_pri2;
 u32 per_pri3;
 u32 ctrl;
 u32 main_mask;
 u32 main_pri1;
 u32 main_pri2;
 u32 reserved1;
 u32 enc_status;
 u32 crit_status;
 u32 main_status;
 u32 per_status;
 u32 reserved2;
 u32 per_error;
};

#endif

#ifndef __ASSEMBLY__

struct mpc52xx_gpt_priv;

#define MPC52XX_LPBFIFO_FLAG_READ (0)
#define MPC52XX_LPBFIFO_FLAG_WRITE (1<<0)
#define MPC52XX_LPBFIFO_FLAG_NO_INCREMENT (1<<1)
#define MPC52XX_LPBFIFO_FLAG_NO_DMA (1<<2)
#define MPC52XX_LPBFIFO_FLAG_POLL_DMA (1<<3)

struct mpc52xx_lpbfifo_request {
 struct list_head list;

 unsigned int cs;
 size_t offset;

 void *data;
 phys_addr_t data_phys;

 size_t size;
 size_t pos;
 int flags;

 void (*callback)(struct mpc52xx_lpbfifo_request *);

 void *priv;

 int irq_count;
 int irq_ticks;
 u8 last_byte;
 int buffer_not_done_cnt;
};

#endif
#endif
