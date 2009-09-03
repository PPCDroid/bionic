/*	$OpenBSD: sigsetjmp.S,v 1.5 2005/08/07 16:40:15 espie Exp $	*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
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
 *	from: @(#)setjmp.s	5.1 (Berkeley) 4/23/90"
 */

#include <sys/linux-syscalls.h>
#include <machine/asm.h>

	.text
	.align 4
	.globl sigsetjmp
	.type sigsetjmp,@function
sigsetjmp:
	cmpwi	4,0	# if zero, do not save/restore signal context
	beq	0f
#ifdef __PIC__
	b setjmp@plt
#else
	b setmp
#endif
0:
#ifdef __PIC__
	b _setjmp@plt
#else
	b _setmp
#endif
	.size sigsetjmp,.-sigsetjmp

	.globl siglongjmp
	.type siglongjmp,@function
siglongjmp:
	cmpwi	4,0	# if zero, do not save/restore signal context
	beq	0f
#ifdef __PIC__
	b longjmp@plt
#else
	b longmp
#endif
0:
#ifdef __PIC__
	b _longjmp@plt
#else
	b _longmp
#endif
	.size siglongjmp,.-siglongjmp
