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
#include <machine/asm.h>
#include <machine/setjmp.h>
#include <sys/regdef.h>

.global __futex_wait
.global __futex_wake

#define FUTEX_WAIT 0
#define FUTEX_WAKE 1

/* val = atomic_cmpxchg(unsigned long oldval, unsigned long newval, void *ptr)
*/
LEAF(__atomic_cmpxchg)
	.set	noreorder

1:
	ll	v1, 0(a2)
	subu	v0, v1, a0
	bne	v0, zero, 2f
	nop
	move	v0, a1
	sc	v0, 0(a2)
	beq	v0, zero, 1b
	xori	v0, v0, 1
2:
	jr	ra
	nop
	.set	reorder
END(__atomic_cmpxchg)

/* val = atomic_swap(long new, long *ptr)
*/
LEAF(__atomic_swap)
	.set	noreorder

1:	ll	v0, 0(a1)
	move	t8, a0
	sc	t8, 0(a1)
	beq	t8, zero, 1b
	nop
	jr	ra
	nop
	.set	reorder
END(__atomic_swap)

/* val = atomic_dec(int *ptr)
*/
LEAF(__atomic_dec)
	.set	noreorder

1:	ll	v0, 0(a0)
	sub	v1, v0, 1
	sc	v1, 0(a0)
	beq	v1, zero, 1b
	nop
	jr	ra
	nop
	.set	reorder
END(__atomic_dec)

/* val = atomic_inc(int *ptr)
*/
LEAF(__atomic_inc)
	.set	noreorder

1:	ll	v0, 0(a0)
	addiu	v1, v0, 1
	sc	v1, 0(a0)
	beq	v1, zero, 1b
	nop
	jr	ra
	nop
	.set	reorder
END(__atomic_inc)

/* __futex_wait(*ftx, val, *timespec) */
/* __futex_wake(*ftx, count) */
/* __futex_syscall(*ftx, op, val, *timespec, *addr2, val3) */

LEAF(__futex_wait)
	.set	noreorder
	.cpload t9
	move	a3, a2
	move	a2, a1
	li	a1, FUTEX_WAIT
	li v0, __NR_futex
	syscall
	.set reorder
	bne a3, zero, 3f
	nop
	jr ra
	nop
3:
#ifdef __PIC__
	la	t9, __set_syscall_errno
	jr	t9
#else
	j       __set_syscall_errno
#endif
	nop
	.set	reorder
END(__futex_wait)

LEAF(__futex_wake)
	.set	noreorder
	.cpload t9
	move	a2, a1
	li	a1, FUTEX_WAKE
	li v0, __NR_futex
	syscall
	.set reorder
	bne a3, zero, 3f
	nop
	jr ra
	nop
3:
#ifdef __PIC__
	la	t9, __set_syscall_errno
	jr	t9
#else
	j       __set_syscall_errno
#endif
	nop
	.set	reorder
END(__futex_wake)
