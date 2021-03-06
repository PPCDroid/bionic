/*-
 * Copyright (c) 2004-2005 David Schultz <das@FreeBSD.ORG>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/lib/msun/arm/fenv.h,v 1.5 2005/03/16 19:03:45 das Exp $
 */

#ifndef	_FENV_H_
#define	_FENV_H_

#include <sys/types.h>

typedef	uint32_t	fenv_t;
typedef	uint32_t	fexcept_t;

/* Exception flags */
#define	FE_INVALID	0x0040
#define	FE_DIVBYZERO	0x0020
#define	FE_OVERFLOW	0x0010
#define	FE_UNDERFLOW	0x0008
#define	FE_INEXACT	0x0004
#define	FE_ALL_EXCEPT	(FE_DIVBYZERO | FE_INEXACT | \
			 FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

/* Rounding modes */
#define	FE_TONEAREST	0x0000
#define	FE_TOWARDZERO	0x0001
#define	FE_UPWARD	0x0002
#define	FE_DOWNWARD	0x0003
#define	_ROUND_MASK	(FE_TONEAREST | FE_DOWNWARD | \
			 FE_UPWARD | FE_TOWARDZERO)
/* __BEGIN_DECLS */

/* Default floating-point environment */
extern const fenv_t	__fe_dfl_env;
#define	FE_DFL_ENV	(&__fe_dfl_env)

/* We need to be able to map status flag positions to mask flag positions */
#define _FPUSW_SHIFT	5
#define	_ENABLE_MASK	(FE_ALL_EXCEPT << _FPUSW_SHIFT)

#define	__cfc1(__fcsr)	__asm __volatile("cfc1 %0,$31" : "=r" (*(__fcsr)))
#define	__ctc1(__fcsr)	__asm __volatile("ctc1 %0,$31" : : "r" (__fcsr))

static __inline int
feclearexcept(int __excepts)
{
	fexcept_t __fcsr;

	__cfc1(&__fcsr);
	__fcsr &= ~__excepts;
	__ctc1(__fcsr);
	return (0);
}

static __inline int
fegetexceptflag(fexcept_t *__flagp, int __excepts)
{
	fexcept_t __fcsr;

	__cfc1(&__fcsr);
	*__flagp = __fcsr & __excepts;
	return (0);
}

static __inline int
fesetexceptflag(const fexcept_t *__flagp, int __excepts)
{
	fexcept_t __fcsr;

	__cfc1(&__fcsr);
	__fcsr &= ~__excepts;
	__fcsr |= *__flagp & __excepts;
	__ctc1(__fcsr);
	return (0);
}

static __inline int
feraiseexcept(int __excepts)
{
	fexcept_t __ex = __excepts;

	fesetexceptflag(&__ex, __excepts);	/* XXX */
	return (0);
}

static __inline int
fetestexcept(int __excepts)
{
	fexcept_t __fcsr;

	__cfc1(&__fcsr);
	return (__fcsr & __excepts);
}

static __inline int
fegetround(void)
{

	/*
	 * Apparently, the rounding mode is specified as part of the
	 * instruction format on ARM, so the dynamic rounding mode is
	 * indeterminate.  Some FPUs may differ.
	 */
	return (-1);
}

static __inline int
fesetround(int __round)
{

	return (-1);
}

static __inline int
fegetenv(fenv_t *__envp)
{

	__cfc1(__envp);
	return (0);
}

static __inline int
feholdexcept(fenv_t *__envp)
{
	fenv_t __env;

	__cfc1(&__env);
	*__envp = __env;
	__env &= ~(FE_ALL_EXCEPT | _ENABLE_MASK);
	__ctc1(__env);
	return (0);
}

static __inline int
fesetenv(const fenv_t *__envp)
{

	__ctc1(*__envp);
	return (0);
}

static __inline int
feupdateenv(const fenv_t *__envp)
{
	fexcept_t __fcsr;

	__cfc1(&__fcsr);
	__ctc1(*__envp);
	feraiseexcept(__fcsr & FE_ALL_EXCEPT);
	return (0);
}

#if __BSD_VISIBLE

static __inline int
feenableexcept(int __mask)
{
	fenv_t __old_fcsr, __new_fcsr;

	__cfc1(&__old_fcsr);
	__new_fcsr = __old_fcsr | (__mask & FE_ALL_EXCEPT) << _FPUSW_SHIFT;
	__ctc1(__new_fcsr);
	return ((__old_fcsr >> _FPUSW_SHIFT) & FE_ALL_EXCEPT);
}

static __inline int
fedisableexcept(int __mask)
{
	fenv_t __old_fcsr, __new_fcsr;

	__cfc1(&__old_fcsr);
	__new_fcsr = __old_fcsr & ~((__mask & FE_ALL_EXCEPT) << _FPUSW_SHIFT);
	__ctc1(__new_fcsr);
	return ((__old_fcsr >> _FPUSW_SHIFT) & FE_ALL_EXCEPT);
}

static __inline int
fegetexcept(void)
{
	fenv_t __fcsr;

	__cfc1(&__fcsr);
	return ((__fcsr & _ENABLE_MASK) >> _FPUSW_SHIFT);
}

#endif /* __BSD_VISIBLE */

/* __END_DECLS */

#endif	/* !_FENV_H_ */
