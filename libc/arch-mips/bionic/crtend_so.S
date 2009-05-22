
#include <sys/regdef.h>

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
	subu	sp, sp, 12
	sw	s0, 0(sp)
	sw	ra, 4(sp)
	la	s0, __CTOR_END__

0:
	/* now grab the next function pointer and check if its -1. If not,
	 * call it, otherwise we're done. We use s0 since it's callee saved.
	 */
	li	v0, -1
	subu	s0, s0, 4
	lw	t9, 0(s0)
	beq	t9, v0, 1f
	nop
	jalr	t9
	nop
	j	0b
	nop

1:
	/* we're done */
	lw	ra, 4(sp)
	lw	s0, 0(sp)
	addiu	sp, sp, 12
	jr	ra

	.section .init
	.align 4
	.set	noreorder
	.cpload t9
	subu	sp, sp, 4
	sw	ra, 0(sp)
	.set	reorder
#ifdef __PIC__
	la	t9, __bionic_call_ctors
	jalr	t9
#else
	jal	__bionic_call_ctors
#endif
	nop
	lw	ra, 0(sp)
	addiu	sp, sp, 4
	jr	ra

	.section .ctors, "aw", @progbits
	.align 2
	.type __CTOR_END__, @object
__CTOR_END__:
	.long 0

	.section .init_array, "aw"
	.long 0

	.section .fini_array, "aw"
	.long 0
