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
#include <machine/asm.h>
#include <sys/linux-syscalls.h>
#include <sys/regdef.h>

/*
 * int  __pthread_clone(int (*fn)(void*), void *tls, int flags, void *arg);
 *
 * We then call:
 *	void __thread_entry(int (*func)(void*), void *arg, void **tls)
 *
 * The TLS is the stack for the new thread.
 */

LEAF(__pthread_clone)
	.set noreorder
	.cpload t9

	sw	a0, -4(a1)	/* Save funct ptr on new thread stack */
	sw	a3, -8(a1)	/* Save arg ptr on new thread stack */
	move	a0, a2		/* put flags into arg0 */
	li v0, __NR_clone
	syscall
	.set reorder
	bne	a3, zero, err	/* not zero is error */
	nop
	beq	v0, zero, child	/* equal zero is child */
	nop
	jr	ra		/* Back to parent */
	nop

	/* We are the child thread.  Set up the calling parameters and
	 * call __thread_entry.
	 */
child:
	lw	a0, -4(sp)	/* Pull funct ptr off new thread stack */
	lw	a1, -8(sp)	/* Pull arg ptr off new thread stack */
	move	a2, sp		/* TLS is above the new thread stack */
#ifdef __PIC__
	la	t9, __thread_entry
	jr	t9
#else
	j       __thread_entry
#endif
	nop

err:
#ifdef __PIC__
    la t9, __set_syscall_errno
    jr t9
#else
    j       __set_syscall_errno
#endif
    nop
	.set	reorder
	END(__pthread_clone)

/* Some Linux native programs need to clone()
*/
LEAF(clone)
	.set noreorder
	.cpload t9

	sw	a0, -4(a1)	/* Save funct ptr on new thread stack */
	sw	a3, -8(a1)	/* Save arg ptr on new thread stack */
	move	a0, a2		/* put flags into arg0 */
	li v0, __NR_clone
	syscall
	.set reorder
	bne	a3, zero, clone_err	/* not zero is error */
	nop
	beq	v0, zero, clone_child	/* equal zero is child */
	nop
	jr	ra			/* Back to parent */
	nop

	/* We are the child thread.  Call func(arg)
	*/
clone_child:
	lw	t9, -4(sp)	/* Pull funct ptr off new thread stack */
	lw	a0, -8(sp)	/* Pull arg ptr off new thread stack */
	jalr	t9

	/* On thred return, just call exit()
	*/
	move	a0, v0

#ifdef __PIC__
	la	t9, _exit
	jr	t9
#else
	j       _exit
#endif
	nop

clone_err:
#ifdef __PIC__
    la t9, __set_syscall_errno
    jr t9
#else
    j       __set_syscall_errno
#endif
    nop
	.set	reorder
	END(clone)
