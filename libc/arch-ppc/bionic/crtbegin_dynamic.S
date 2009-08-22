# bionic/arch-ppc/bionic/crtbegin_dynamic.S
#
# Copyright 2006, The Android Open Source Project
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Google Inc. nor the names of its contributors may
#       be used to endorse or promote products derived from this software
#       without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY Google Inc. ``AS IS'' AND ANY EXPRESS OR 
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
# EVENT SHALL Google Inc. BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	.text
	.align 4
	.type _start, @function
	.type __libc_init, @function
	.globl _start

# this is the small startup code that is first run when
# any executable that is statically-linked with Bionic
# runs.
#
# it's purpose is to call __libc_init with appropriate
# arguments, which are:
#
#    - the address of the raw data block setup by the Linux
#      kernel ELF loader
#
#    - address of an "onexit" function, not used on any
#      platform supported by Bionic
#
#    - address of the "main" function of the program. We
#      can't hard-code it in the adr pseudo instruction
#      so we use a tiny trampoline that will get relocated
#      by the dynamic linker before this code runs
#
#    - address of the constructor list
#
_start:	
	/* save sp */
	mr	9,1
	clrrwi	1,1,4
#ifdef __PIC__
#ifdef HAVE_ASM_PPC_REL16
	bcl	20,31,1f	/* BO=20 (branch unconditionally) */
				/* BI=31 (don't care) */
1:	mflr	31
	addis	31,31,_GLOBAL_OFFSET_TABLE_-1b@ha
	addi	31,31,_GLOBAL_OFFSET_TABLE_-1b@l
#else
	bl	_GLOBAL_OFFSET_TABLE_-4@local
	mflr	31
#endif
#endif
	/* small data pointer in 13 */
#ifdef __PIC__
	lwz	13,_SDA_BASE_@got(r31)
#else
	lis	13,_SDA_BASE_@ha
	addi	13,13,_SDA_BASE_@l
#endif
	stwu	1,-16(1)	/* initial stack frame */
	li	0,0		/* clear lr */
	mtlr	0
	stw	0,0(1)		/* save to stack frame */

	mr	3,9		/* original stack pointer */
	li	4,0		/* onexit (unused) */
	lis	5,0f@ha		/* slingshot */
	addi	5,5,0f@l
	lis	6,1f@ha
	addi	6,6,1f@l
#ifdef __PIC__
	bl	__libc_init@plt
#else
	bl	__libc_init
#endif

0:
#ifdef __PIC__
	b	main@plt
#else
	b	main
#endif

1:  .long   __PREINIT_ARRAY__
    .long   __INIT_ARRAY__
    .long   __FINI_ARRAY__
    .long   __CTOR_LIST__
      
# the .ctors section contains a list of pointers to "constructor"
# functions that need to be called in order during C library initialization,
# just before the program is being run. This is a C++ requirement
#
# the last entry shall be 0, and is defined in crtend.S
#
	.section .preinit_array, "aw"
	.globl __PREINIT_ARRAY__
__PREINIT_ARRAY__:
	.long -1

	.section .init_array, "aw"
	.globl __INIT_ARRAY__
__INIT_ARRAY__:
	.long -1

	.section .fini_array, "aw"
	.globl __FINI_ARRAY__
__FINI_ARRAY__:
	.long -1

	.section .ctors, "aw"
	.globl __CTOR_LIST__
__CTOR_LIST__:
	.long -1

