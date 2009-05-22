/* From: NetBSD: setjmp.h,v 1.2 1997/04/06 08:47:41 cgd Exp */

/*-
 * Copyright (c) 1994, 1995 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Author: Chris G. Demetriou
 *
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 *
 *	JNPR: setjmp.h,v 1.2 2006/12/02 09:53:41 katta
 * $FreeBSD$
 */

#ifndef _MACHINE_SETJMP_H_
#define	_MACHINE_SETJMP_H_

/*
 * machine/setjmp.h: machine dependent setjmp-related information.
 */

#define	_JBLEN	95		/* size, in longs, of a jmp_buf */

/*
 * Description of the setjmp buffer
 *
 * word  0	magic number	(dependant on creator)
 *       1	RA
 *       2	S0
 *       3	S1
 *       4	S2
 *       5	S3
 *       6	S4
 *       7	S5
 *       8	S6
 *       9	S7
 *       10	SP
 *       11	S8
 *       12	signal mask	(dependant on magic)
 *       13	(con't)
 *       14	(con't)
 *       15	(con't)
 *
 * The magic number number identifies the jmp_buf and
 * how the buffer was created as well as providing
 * a sanity check
 *
 */

#define _JB_MAGIC__SETJMP	0xBADFACED
#define _JB_MAGIC_SETJMP	0xFACEDBAD

/* Valid for all jmp_buf's */

#define _JB_MAGIC		0
#define _JB_REG_RA		1
#define _JB_REG_S0		2
#define _JB_REG_S1		3
#define _JB_REG_S2		4
#define _JB_REG_S3		5
#define _JB_REG_S4		6
#define _JB_REG_S5		7
#define _JB_REG_S6		8
#define _JB_REG_S7		9
#define _JB_REG_SP		10
#define _JB_REG_S8		11

/* Only valid with the _JB_MAGIC_SETJMP magic */

#define _JB_SIGMASK		12

#endif /* _MACHINE_SETJMP_H_ */
