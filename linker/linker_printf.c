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

/* based on BSD's _dl_printf */

/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)printf.c	8.1 (Berkeley) 6/11/93
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/stat.h>

#include <sys/mman.h>
#include <sys/linux-syscalls.h>

#include "linker.h"
#include "linker_debug.h"

/* output a single character to an already open fd */
/* note that we use a direct syscall, and don't use libc at all */
/* that way, we can use printf very early in the linker boot sequence */

static void putcharfd(char c, int fd)
{
#if defined(ANDROID_PPC_LINKER)
    asm volatile (
            "mr 3,%1    \n" /* r3 = fd */
            "mr 4,%2    \n" /* r4 = &b */
            "li 5,1     \n" /* len = 1 */
            "li 0,%0    \n" /* system call number */
            "sc         \n" /* we ignore the return */
            : : "I"(__NR_write), "r"(fd), "r"(&c) :
            "0", "3", "4", "5", "cc");
#else
    write(fd, &c, 1);
#endif
}

/* format flags */
#define LFLAG (1 << 0) /* l modifier */
#define MFLAG (1 << 1) /* - modifier */
#define ZFLAG (1 << 2) /* 0 first */
#define DFLAG (1 << 3) /* digit format */
#define DVAL(x) (((x) & 0xFFFF) << 16)    /* digits */
#define GET_DVAL(x) ((unsigned int)(x) >> 16)
#define SET_DVAL(x, v) \
    do { (x) = ((unsigned int)(v) << 16) | ((x) & 0xffff); } while(0)

static int kprintn(void (*putc_hook)(char c, int fd), int fd, unsigned long ul,
        int base, unsigned int flags)
{
	/* hold a long in base 8 */
	char *p;
	char buf[64];
    int cnt;
    unsigned int digits, len;

    digits = GET_DVAL(flags);

    cnt = 0;
	p = buf;
	do {
		*p++ = "0123456789abcdef"[ul % base];
	} while (ul /= base);
    len = p - buf;

    if ((flags & MFLAG) == 0) {
        while (len < digits) {
            if (flags & ZFLAG)
                (*putc_hook)('0', fd);
            else
                (*putc_hook)(' ', fd);
            cnt++;
            len++;
        }
    }

	do {
		(*putc_hook)(*--p, fd);
        cnt++;
	} while (p > buf);

    if ((flags & MFLAG) != 0) {
        while (len < digits) {
            (*putc_hook)(' ', fd);
            cnt++;
            len++;
        }
    }

    return cnt;
}

static int kdoprnt(void (*putc_hook)(char c, int fd), int fd,
        const char *fmt, va_list ap)
{
	unsigned long ul;
    unsigned int flags;
    char ch;
    int cnt;
    unsigned int digits, len;
	char *p;

    cnt = 0;
	for (;;) {
		while ((ch = *fmt++) != '%') {
			if (ch == '\0')
				return cnt;
			(*putc_hook)(ch, fd);
            cnt++;
		}
		flags = 0;
reswitch:
		switch (ch = *fmt++) {
		case 'l':
			flags |= LFLAG;
			goto reswitch;
        case '-':   /* ignore these */
            flags |= MFLAG;
            goto reswitch;
        case '0'...'9':
            if (ch == '0' && (flags & DFLAG) == 0)
                flags |= ZFLAG;
            flags |= DFLAG;
            /* format digits */
            digits = GET_DVAL(flags);
            digits *= 10;
            digits += ch - '0';
            SET_DVAL(flags, digits);
            goto reswitch;
		case 'c':
			ch = va_arg(ap, int);
			(*putc_hook)(ch & 0x7f, fd);
            cnt++;
			break;
		case 's':
			p = va_arg(ap, char *);

            /* calculate len */
            len = 0;
            while (p[len] != '\0')
                len++;

            digits = GET_DVAL(flags);

            if ((flags & MFLAG) == 0) {
                while (len < digits) {
                    (*putc_hook)(' ', fd);
                    cnt++;
                    len++;
                }
            }

			while ((ch = *p++)) {
				(*putc_hook)(ch, fd);
                cnt++;
            }

            if ((flags & MFLAG) != 0) {
                while (len < digits) {
                    (*putc_hook)(' ', fd);
                    cnt++;
                    len++;
                }
            }

			break;
		case 'd':
			ul = (flags & LFLAG) ? va_arg(ap, long) : va_arg(ap, int);
			if ((long)ul < 0) {
				(*putc_hook)('-', fd);
                cnt++;
				ul = -(long)ul;
			}
			cnt += kprintn(putc_hook, fd, ul, 10, flags);
			break;
		case 'o':
			ul = (flags & LFLAG) ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
			cnt += kprintn(putc_hook, fd, ul, 8, flags);
			break;
		case 'u':
			ul = (flags & LFLAG) ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
			cnt += kprintn(putc_hook, fd, ul, 10, flags);
			break;
		case 'p':
			(*putc_hook)('0', fd);
			(*putc_hook)('x', fd);
            cnt += 2;
            if (sizeof(void *) == sizeof(unsigned long))
                flags |= LFLAG;
		case 'x':
			ul = (flags & LFLAG) ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
			cnt += kprintn(putc_hook, fd, ul, 16, flags);
			break;
		case 'X':
		{
			int l;

			ul = (flags & LFLAG) ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
			if (flags & LFLAG)
				l = (sizeof(unsigned long) * 8) - 4;
			else
				l = (sizeof(unsigned int) * 8) - 4;
			while (l >= 0) {
				(*putc_hook)("0123456789abcdef"[(ul >> l) & 0xf], fd);
                cnt++;
				l -= 4;
			}
			break;
		}
		default:
			(*putc_hook)('%', fd);
            cnt++;
			if (flags & LFLAG) {
				(*putc_hook)('l', fd);
                cnt++;
            }
			(*putc_hook)(ch, fd);
            cnt++;
		}
	}
	va_end(ap);

    return cnt;
}

int linker_printf(const char *fmt, ...)
{
	va_list ap;
    int cnt;

	va_start(ap, fmt);
	cnt = kdoprnt(putcharfd, 1, fmt, ap);
	va_end(ap);

    return cnt;
}

int linker_vprintf(const char *fmt, va_list ap)
{
	return kdoprnt(putcharfd, 1, fmt, ap);
}
