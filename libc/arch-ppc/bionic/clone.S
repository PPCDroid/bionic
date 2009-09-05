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
#include <sys/linux-syscalls.h>

	.text
	.align 4

/*
 * int  __pthread_clone(int (*fn)(void*), void *tls, int flags,
 *                      void *arg);
 */
	.globl __pthread_clone
	.type __pthread_clone,@function
__pthread_clone:
	/* r3 is fn, r4 = tls, r5 = flags, r6 = arg */
	stw	3,-4(4)	/* save fn */
	stw	6,-8(4) /* save arg */

	/* int sys_clone(unsigned long clone_flags (r3), unsigned long newsp (r4), 
		 int __user *parent_tidptr (r5), int tls_val (r6), int *child_tidptr (r7), struct pt_regs *regs (r8))
	*/
	mr 3,5	/* r3=clone_flags */
			/* r4=tls -> newsp */
			/* r5=parent_tidptr (only referenced if (clone_flags & CLONE_PARENT_SETTID) != 0 */
	li 6,0
	li 7,0
	li 8,0

	li 0, __NR_clone
	sc
	bns+ 0f
	b __set_syscall_errno
0:	cmpwi 3,0	/* zero? */
	bnelr		/* parent returns here */
	/* child */
	lwz 3,-4(1)	/* r0 -> func */
	mr 5, 1		/* r4 -> tls */
	lwz 4,-8(1)	/* r3 -> arg */

	/* initial stack frame */
	stwu	1,-16(1)	/* initial stack frame */
	li	0,0		/* clear lr */
	mtlr	0
	stw	0,0(1)		/* save to stack frame */

#ifdef __PIC__
	b __thread_entry@plt
#else
	b __thread_entry
#endif
	.size __pthread_clone,.-__pthread_clone

