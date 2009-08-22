/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _ASM_POWERPC_SWAB_H
#define _ASM_POWERPC_SWAB_H

#include <asm/types.h>

#ifdef __GNUC__

#ifndef __powerpc64__
#define __SWAB_64_THRU_32__
#endif

/* XXX these were protected by a KERNEL define
   so the __u16/__u32 types are not available, converted to gcc 
   uint16_t, uint32_t types which should be always available */

#include <stdint.h>

static __inline__ uint16_t ld_le16(const volatile uint16_t *addr)
{
	uint16_t val;

	__asm__ __volatile__ ("lhbrx %0,0,%1" : "=r" (val) : "r" (addr), "m" (*addr));
	return val;
}
#define __arch_swab16p ld_le16

static __inline__ void st_le16(volatile uint16_t *addr, const uint16_t val)
{
	__asm__ __volatile__ ("sthbrx %1,0,%2" : "=m" (*addr) : "r" (val), "r" (addr));
}

static inline void __arch_swab16s(uint16_t *addr)
{
	st_le16(addr, *addr);
}
#define __arch_swab16s __arch_swab16s

static __inline__ uint32_t ld_le32(const volatile uint32_t *addr)
{
	uint32_t val;

	__asm__ __volatile__ ("lwbrx %0,0,%1" : "=r" (val) : "r" (addr), "m" (*addr));
	return val;
}
#define __arch_swab32p ld_le32

static __inline__ void st_le32(volatile uint32_t *addr, const uint32_t val)
{
	__asm__ __volatile__ ("stwbrx %1,0,%2" : "=m" (*addr) : "r" (val), "r" (addr));
}

static inline void __arch_swab32s(uint32_t *addr)
{
	st_le32(addr, *addr);
}
#define ___arch_swab32s __arch_swab32s

static inline __attribute__((const)) uint16_t __arch_swab16(uint16_t value)
{
	uint16_t result;

	__asm__("rlwimi %0,%1,8,16,23"
	    : "=r" (result)
	    : "r" (value), "0" (value >> 8));
	return result;
}
#define __arch__swab16 __arch_swab16
#define __arch_swab16 __arch_swab16

static inline __attribute__((const)) uint32_t __arch_swab32(uint32_t value)
{
	uint32_t result;

	__asm__("rlwimi %0,%1,24,16,23\n\t"
	    "rlwimi %0,%1,8,8,15\n\t"
	    "rlwimi %0,%1,24,0,7"
	    : "=r" (result)
	    : "r" (value), "0" (value >> 24));
	return result;
}
#define __arch__swab32 __arch_swab32
#define __arch_swab32 __arch_swab32

#endif

#endif
