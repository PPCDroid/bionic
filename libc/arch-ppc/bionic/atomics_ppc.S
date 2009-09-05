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

#define FUTEX_WAIT 0
#define FUTEX_WAKE 1

	.text
	.align 4

	/* int __atomic_cmpxchg(int old, int new, volatile int* addr) */

	.globl __atomic_cmpxchg
	.type __atomic_cmpxchg,@function
__atomic_cmpxchg:
	/* r6 has result */
1:	lwarx	6,0,5	/* read lock & reserve */
	cmpw	0,6,3	/* compare with old value */
	bne-	2f	/* not equal, get out */
	stwcx.	4,0,5	/* try to set lock */
	bne-	1b	/* fails, try again */
	li	3,0	/* return 0 on success */
	blr
2:	li	3,1	/* return 1 on failure */
	blr
	.size __atomic_cmpxchg,.-__atomic_cmpxchg

	/* int __atomic_swap(int new, volatile int* addr) */

	.globl __atomic_swap
	.type __atomic_swap,@function
__atomic_swap:
0:	lwarx	6,0,4	/* read lock & reserve */
	stwcx.	3,0,4	/* try to set lock */
	bne-	0b	/* loop until swap is successful */
	mr	3,6	/* old value in r3 */
	blr
	.size __atomic_swap,.-__atomic_swap

	/* int __atomic_dec(volatile int* addr) */

	.globl __atomic_dec
	.type __atomic_dec,@function
__atomic_dec:
0:	lwarx	6,0,3	/* read lock & reserve */
	addic	5,6,-1	/* decrement */
	stwcx.	5,0,3	/* try to set lock */
	bne-	0b	/* loop until swap is successful */
	mr	3,6	/* old value in r3 */
	blr
	.size __atomic_dec,.-__atomic_dec

	/* int __atomic_inc(volatile int* addr) */

	.globl __atomic_inc
	.type __atomic_inc,@function
__atomic_inc:
0:	lwarx	6,0,3	/* read lock & reserve */
	addic	5,6,1	/* increment */
	stwcx.	5,0,3	/* try to set lock */
	bne-	0b	/* loop until swap is successful */
	mr	3,6	/* old value in r3 */
	blr
	.size __atomic_inc,.-__atomic_inc

	/* int __futex_wait(volatile void *ftx, int val, const struct timespec *timeout) */
	.globl __futex_wait
	.type __futex_wait,@function
__futex_wait:
	mr 6, 5 		/* r6 - timeout */
	mr 5, 4			/* r5 - val */
	li 4, FUTEX_WAIT	/* r4 op */
				/* r3 - ftx */
	li 0, __NR_futex
	sc
	bnslr+
	b   __set_syscall_errno
	blr
	.size __futex_wait,.-__futex_wait

	/* int __futex_wake(volatile void *ftx, int count) */

	.globl __futex_wake
	.type __futex_wake,@function
__futex_wake:
	mr 5, 4			/* r5 - count */
	li 4, FUTEX_WAKE	/* r4 op */
				/* r3 - ftx */
	li  0, __NR_futex
	sc
	bnslr+
	b   __set_syscall_errno
	blr
	.size __futex_wake,.-__futex_wake
