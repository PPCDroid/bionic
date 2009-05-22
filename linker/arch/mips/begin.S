/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <sys/regdef.h>

	.text
	.align 2
	.type __start,@function
	.globl __start

__start:
	bal	3f
	.word	_gp
3:
	lw	gp, 0(ra)
	move	a0, sp
	li	a1, 0
	jal	__linker_init

	/* linker init returns the _entry address in the main image */
	jr	v0
	nop

/* This gets called from the MIPS.stubs section to resolve the DSO
 * function linkage.  Upon calling, we get:
 *	current (old) gp
 *	C caller ra in t7
 *	string index in t8
 *	our address in t9
 */
	.globl	___resolve_stubs
___resolve_stubs:
	.set	noreorder
	subu	sp, sp, 28
	move	v0, gp
	addiu	t9, t9, 12
	.cpload	t9		/* get our gp */
	.set	reorder
	move	v1, ra
	.cprestore 24
	sw	t7, 20(sp)
	sw	a0, 16(sp)
	sw	a1, 12(sp)
	sw	a2, 8(sp)
	sw	a3, 4(sp)
	move	a0, t8
	lh	a1, -16(v1)
	addu	a1, a1, v0
	la	t9, _stub_helper
	jalr	t9
	nop
	lw	ra, 20(sp)
	lw	a0, 16(sp)
	lw	a1, 12(sp)
	lw	a2, 8(sp)
	lw	a3, 4(sp)
	addiu	sp, sp, 28
	move	t9, v0
	jr	t9
	nop


	.section .ctors, "wa"
	.globl __CTOR_LIST__
__CTOR_LIST__:
	.long -1
