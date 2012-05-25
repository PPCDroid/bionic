/*
 * Copyright (C) 2012 The Android Open Source Project
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

        .gnu_attribute 4, 1
        .gnu_attribute 8, 1
        .gnu_attribute 12, 2
	.text
	.align 2
	.globl atexit
	.hidden atexit
	.type atexit, @function
atexit:
        stwu 1,-16(1)
        mflr 0
        stw 0,20(1)
        stw 30,8(1)
#if defined(__PIC__)
        bcl 20,31,3f
3:
        mflr 30
        addis 30,30,_GLOBAL_OFFSET_TABLE_-3b@ha
        addi 30,30,_GLOBAL_OFFSET_TABLE_-3b@l
        lwz 5,__dso_handle@got(30)
#else
	lis 5,__dso_handle@ha
	addi 5,5,__dso_handle@l
#endif
	lwz 5,0(5)
        li 4,0
        bl __cxa_atexit@plt
        lwz 0,20(1)
        mtlr 0
        lwz 30,8(1)
        addi 1,1,16
	blr
	.size	atexit, .-atexit
