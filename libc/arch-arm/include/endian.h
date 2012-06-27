/*	$OpenBSD: endian.h,v 1.3 2005/12/13 00:35:23 millert Exp $	*/

#undef _BYTE_ORDER
#ifdef __ARMEB__
#define _BYTE_ORDER _BIG_ENDIAN
#else
#define _BYTE_ORDER _LITTLE_ENDIAN
#endif
#define	__STRICT_ALIGNMENT
#define ARCH_ENDIAN_INCLUDED
#include <sys/types.h>
#include <sys/endian.h>
