/*	$NetBSD: asm.h,v 1.29 2000/12/14 21:29:51 jeffs Exp $	*/

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)machAsmDefs.h	8.1 (Berkeley) 6/10/93
 *	JNPR: asm.h,v 1.10 2007/08/09 11:23:32 katta
 * $FreeBSD$
 */

/*
 * machAsmDefs.h --
 *
 *	Macros used when writing assembler programs.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 *
 * from: Header: /sprite/src/kernel/mach/ds3100.md/RCS/machAsmDefs.h,
 *	v 1.2 89/08/15 18:28:24 rab Exp  SPRITE (DECWRL)
 */

#ifndef _MIPS_ASM_H_
#define	_MIPS_ASM_H_

#include <machine/endian.h>

/*
 * Define -pg profile entry code.
 * Must always be noreorder, must never use a macro instruction
 * Final addiu to t9 must always equal the size of this _KERN_MCOUNT
 */
#define	_KERN_MCOUNT			\
	.set	push;			\
	.set	noreorder;		\
	.set	noat;			\
	subu	sp,sp,16;		\
	sw	t9,12(sp);		\
	move	AT,ra;			\
	lui	t9,%hi(_mcount);	\
	addiu	t9,t9,%lo(_mcount);	\
	jalr	t9;			\
	nop;				\
	lw	t9,4(sp);		\
	addiu	sp,sp,8;		\
	addiu	t9,t9,40;		\
	.set	pop;

#ifdef GPROF
#define	MCOUNT _KERN_MCOUNT
#else
#define	MCOUNT
#endif

#define	_C_LABEL(x)	x

/* 
 *  Endian-independent assembly-code aliases for unaligned memory accesses.
 */
#if BYTE_ORDER == LITTLE_ENDIAN
#define	LWLO	lwl
#define	LWHI	lwr
#define	SWLO	swl
#define	SWHI	swr
#endif

#if BYTE_ORDER == BIG_ENDIAN
#define	LWLO	lwr
#define	LWHI	lwl
#define	SWLO	swr
#define	SWHI	swl
#endif

#ifdef USE_AENT
#define	AENT(x)		\
	.aent	x, 0
#else
#define	AENT(x)
#endif

/*
 * WARN_REFERENCES: create a warning if the specified symbol is referenced
 */
#define	WARN_REFERENCES(_sym,_msg)				\
	.section .gnu.warning. ## _sym ; .ascii _msg ; .text

/*
 * These are temp registers whose names can be used in either the old
 * or new ABI, although they map to different physical registers.  In
 * the old ABI, they map to t4-t7, and in the new ABI, they map to a4-a7.
 *
 * Because they overlap with the last 4 arg regs in the new ABI, ta0-ta3
 * should be used only when we need more than t0-t3.
 */
#if defined(__mips_n32) || defined(__mips_n64)
#define ta0     $8
#define ta1     $9
#define ta2     $10
#define ta3     $11
#else
#define ta0     $12
#define ta1     $13
#define ta2     $14
#define ta3     $15
#endif /* __mips_n32 || __mips_n64 */

#ifdef __ELF__
# define _C_LABEL(x)    x
#else
#  define _C_LABEL(x)   _ ## x
#endif

/*
 * WEAK_ALIAS: create a weak alias.
 */
#define	WEAK_ALIAS(alias,sym)						\
	.weak alias;							\
	alias = sym

/*
 * STRONG_ALIAS: create a strong alias.
 */
#define STRONG_ALIAS(alias,sym)						\
	.globl alias;							\
	alias = sym

#define	GLOBAL(sym)						\
	.globl sym; sym:

#define	ENTRY(sym)						\
	.text; .globl sym; .ent sym; sym:

#define	ASM_ENTRY(sym)						\
	.text; .globl sym; .type sym,@function; sym:

/*
 * LEAF
 *	A leaf routine does
 *	- call no other function,
 *	- never use any register that callee-saved (S0-S8), and
 *	- not use any local stack storage.
 */
#define	LEAF(x)			\
	.globl	_C_LABEL(x);	\
	.ent	_C_LABEL(x), 0;	\
_C_LABEL(x): ;			\
	.frame sp, 0, ra;	\
	MCOUNT

/*
 * LEAF_NOPROFILE
 *	No profilable leaf routine.
 */
#define	LEAF_NOPROFILE(x)	\
	.globl	_C_LABEL(x);	\
	.ent	_C_LABEL(x), 0;	\
_C_LABEL(x): ;			\
	.frame	sp, 0, ra

/*
 * XLEAF
 *	declare alternate entry to leaf routine
 */
#define	XLEAF(x)		\
	.globl	_C_LABEL(x);	\
	AENT (_C_LABEL(x));	\
_C_LABEL(x):

/*
 * NESTED
 *	A function calls other functions and needs
 *	therefore stack space to save/restore registers.
 */
#define	NESTED(x, fsize, retpc)		\
	.globl	_C_LABEL(x);		\
	.ent	_C_LABEL(x), 0;		\
_C_LABEL(x): ;				\
	.frame	sp, fsize, retpc;	\
	MCOUNT

/*
 * NESTED_NOPROFILE(x)
 *	No profilable nested routine.
 */
#define	NESTED_NOPROFILE(x, fsize, retpc)	\
	.globl	_C_LABEL(x);			\
	.ent	_C_LABEL(x), 0;			\
_C_LABEL(x): ;					\
	.frame	sp, fsize, retpc

/*
 * XNESTED
 *	declare alternate entry point to nested routine.
 */
#define	XNESTED(x)		\
	.globl	_C_LABEL(x);	\
	AENT (_C_LABEL(x));	\
_C_LABEL(x):

/*
 * END
 *	Mark end of a procedure.
 */
#define	END(x)			\
	.end _C_LABEL(x)

/*
 * IMPORT -- import external symbol
 */
#define	IMPORT(sym, size)	\
	.extern _C_LABEL(sym),size

/*
 * EXPORT -- export definition of symbol
 */
#define	EXPORT(x)		\
	.globl	_C_LABEL(x);	\
_C_LABEL(x):

/*
 * XXX retain dialects XXX
 */
#define	ALEAF(x)			XLEAF(x)
#define	NLEAF(x)			LEAF_NOPROFILE(x)
#define	NON_LEAF(x, fsize, retpc)	NESTED(x, fsize, retpc)
#define	NNON_LEAF(x, fsize, retpc)	NESTED_NOPROFILE(x, fsize, retpc)

/*
 *    standard callframe {
 *        register_t cf_args[4];          arg0 - arg3
 *        register_t cf_sp;               frame pointer
 *        register_t cf_ra;               return address
 *    };
 */
#define CALLFRAME_SIZ   (4 * (4 + 2))
#define CALLFRAME_SP    (4 * 4)
#define CALLFRAME_RA    (4 * 5)
#define START_FRAME     CALLFRAME_SIZ
#define SZREG		4


#endif /* !_MIPS_ASM_H_ */
