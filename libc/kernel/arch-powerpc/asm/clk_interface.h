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
#ifndef __ASM_POWERPC_CLK_INTERFACE_H
#define __ASM_POWERPC_CLK_INTERFACE_H

#include <linux/clk.h>

struct clk_interface {
 struct clk* (*clk_get) (struct device *dev, const char *id);
 int (*clk_enable) (struct clk *clk);
 void (*clk_disable) (struct clk *clk);
 unsigned long (*clk_get_rate) (struct clk *clk);
 void (*clk_put) (struct clk *clk);
 long (*clk_round_rate) (struct clk *clk, unsigned long rate);
 int (*clk_set_rate) (struct clk *clk, unsigned long rate);
 int (*clk_set_parent) (struct clk *clk, struct clk *parent);
 struct clk* (*clk_get_parent) (struct clk *clk);
};

#endif