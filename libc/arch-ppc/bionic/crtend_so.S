

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
	stwu 1,-16(1)   /* make stack frame */
	stw 0,20(1)
    stw 29,8(1)     /* save 29 */

#if defined(__PIC__)
	lwz	29,__CTOR_LIST__@got(31)
#else
	lis	29,__CTOR_LIST__@ha
	addi 29,29,__CTOR_LIST__@l
#endif
	lwz	3,0(29)
	cmpwi 3,-1  /* if -1 not found end */
	bne	1f
2:  addi 29,29,4
	lwz	3,0(29)
	cmpwi 3,0  /* if 0 end of list */
	bne	2b
0:
	/* now grab the next function pointer and check if its -1. */
	/*   If not, call it, otherwise we're done. */
	addi 29,29,-4
	lwz	3,0(29)
	cmpwi 3,-1  /* if -1 found end */
	beq	1f
    cmpwi 3,0   /* if 0 we screwed up */
    beq 1f

	/* call constructor */
	mtlr 3
	blrl
	b 0b
1:
    lwz 29,8(1)     /* restore r29 */
	lwz 0,20(1)
	addi 1,1,16
	mtlr 0
	blr
	.size __bionic_call_ctors,.-__bionic_call_ctors

.section .data
.align 4
	.globl __libc_stack_end
__libc_stack_end:
	.long	0

    .section .init
    mflr 0
    stwu 1,-16(1)
    stw 0,20(1)
    bl __bionic_call_ctors
    lwz 0,20(1)
    addi 1,1,16
    mtlr 0
    blr

	.section .init_array, "aw"
	.long 0

	.section .fini_array, "aw"
	.long 0

/*	.section .ctors, "aw", @progbits */
/*	.type __CTOR_END___, @object */
	.section .ctors, "aw"
__CTOR_END___:
	.long 0
