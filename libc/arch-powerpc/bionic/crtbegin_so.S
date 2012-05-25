/*
 * Copyright (C) 2008, 2012 The Android Open Source Project
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

	.text
	.align 4
	.type __bionic_on_dlclose, @function
__bionic_on_dlclose:
	mflr 0
	stwu 1,-16(1)
	stw 0,20(1)
	stw 30,8(1)
#if defined(__PIC__)
	bcl 20,31,3f
3:
	mflr 30
	addis 30,30,_GLOBAL_OFFSET_TABLE_-3b@ha
	addi 30,30,_GLOBAL_OFFSET_TABLE_-3b@l
	lwz 9,__dso_handle@got(30)
#else
	lis 9,__dso_handle@ha
	addi 9,9,__dso_handle@l
#endif
	lwz 3,0(9)
	bl __cxa_finalize@plt
	lwz 0,20(1)
	mtlr 0
	lwz 30,8(1)
	addi 1,1,16
	blr

	.size __bionic_on_dlclose,.-__bionic_on_dlclose

	.section .init_array, "aw"
	.globl __INIT_ARRAY__
__INIT_ARRAY__:
	.long -1

        .section .fini_array, "aw"
        .globl __FINI_ARRAY__
__FINI_ARRAY__:
        .long -1
	.long __bionic_on_dlclose

#include "__dso_handle_so.S"
#include "atexit.S"
