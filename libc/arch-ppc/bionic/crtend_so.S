.text
.align 4
.type __bionic_call_ctors, @function

/*
 * The CTORS_LIST is marked by -1 (start) and 0 (end).
 * We mark the end of the .ctors section with the __CTOR_END__ section so
 * that we can just iterate backwards from it until we hit -1 and execute
 * all the function pointers. This seems to be the way to do it for SVR4
 * derived systems.
 */
__bionic_call_ctors:
	/* stack frame */
        mflr 0
	stwu 1,-16(1)
	stw 0,20(1)

#ifdef __PIC__
	lwz	3,__CTOR_END___@got(31)
#else
	lis	3,__CTOR_END___@ha
	addi	3,3,__CTOR_END___@l
#endif

	li	0,-1
0:
	/* now grab the next function pointer and check if its -1. */
	/*   If not, call it, otherwise we're done. */
	addi	3,3,-4
	lwz	4,0(3)
	cmpw	4,0
	beq	1f

	/* call constructor */
	mtlr	4
	blrl
	b	0b
1:
	lwz 0,20(1)
	addi 1,1,16
	mtlr 0
	blr

.section .data
.align 4
	.globl __libc_stack_end
__libc_stack_end:
	.long	0

.section .init
.align 4
 	bl __bionic_call_ctors
	blr

.section .ctors, "aw", @progbits
.align 4
.type __CTOR_END___, @object
__CTOR_END___:
	.long 0

.section .init_array, "aw"
	.long 0

.section .fini_array, "aw"
	.long 0
