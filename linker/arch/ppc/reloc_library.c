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

#include <linux/auxvec.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/stat.h>

#include <pthread.h>

#include <sys/mman.h>

#include <sys/atomics.h>

/* special private C library header - see Android.mk */
#include <bionic_tls.h>

#include "linker.h"
#include "linker_debug.h"

#include "ba.h"

/* relocation bits */
#define HA(x) (((unsigned)(x) >> 16) + (((unsigned)(x) & 0x00008000) >> 15))
#define L(x) (((unsigned)x) & 0x0000ffff)
#define ADDIS_R11_R11	0x3d6b0000
#define ADDIS_R11_R0	0x3d600000
#define ADDI_R11_R11	0x396b0000
#define LWZ_R11_R11	0x816b0000
#define LI_R11		0x39600000

#define ADDIS_R12_R0	0x3d800000
#define ADDI_R12_R12	0x398c0000
#define MCTR_R11	0x7d6903a6
#define MCTR_R12	0x7d8903a6
#define BCTR		0x4e800420
#define BR(from, to)	do { \
	int lval = (unsigned)(to) - (unsigned)(&(from)); \
	lval &= ~0xfc000000; \
	lval |= 0x48000000; \
	(from) = lval; \
} while (0)

/* these are structures/functions offset from PLT region */
#define PLT_CALL_OFFSET		6
#define PLT_INFO_OFFSET		10
#define PLT_1STRELA_OFFSET	18
#define B24_VALID_RANGE(x) \
    ((((x) & 0xfe000000) == 0x00000000) || (((x) &  0xfe000000) == 0xfe000000))

static inline void dcbf(Elf32_Addr *addr)
{
	asm volatile ("dcbst 0, %0\n\t"
		"sync\n\t"
		"icbi 0, %0\n\t"
		"sync\n\t"
		"isync"
		: : "r" (addr) : "0");
}


/* >>> IMPORTANT NOTE - READ ME BEFORE MODIFYING <<<
 *
 * Do NOT use malloc() and friends or pthread_*() code here.
 * Don't use printf() either; it's caused mysterious memory
 * corruption in the past.
 * The linker runs before we bring up libc and it's easiest
 * to make sure it does not depend on any complex libc features
 *
 */

#ifdef LINKER_DEBUG

struct reloc_desc {
	unsigned val;
	const char *text;
};

#undef R_PPC
#define R_PPC(x) { .val = R_PPC_ ## x, .text = "R_PPC_" #x , }

static const struct reloc_desc reloc_desc_tab[] = {
	R_PPC(NONE),
	R_PPC(ADDR32),
	R_PPC(ADDR24),
	R_PPC(ADDR16),
	R_PPC(ADDR16_LO),
	R_PPC(ADDR16_HI),
	R_PPC(ADDR16_HA),
	R_PPC(ADDR14),
	R_PPC(ADDR14_BRTAKEN),
	R_PPC(ADDR14_BRNTAKEN),
	R_PPC(REL24),
	R_PPC(REL14),
	R_PPC(REL14_BRTAKEN),
	R_PPC(REL14_BRNTAKEN),
	R_PPC(GOT16),
	R_PPC(GOT16_LO),
	R_PPC(GOT16_HI),
	R_PPC(GOT16_HA),
	R_PPC(PLTREL24),
	R_PPC(COPY),
	R_PPC(GLOB_DAT),
	R_PPC(JMP_SLOT),
	R_PPC(RELATIVE),
	R_PPC(LOCAL24PC),
	R_PPC(UADDR32),
	R_PPC(UADDR16),
	R_PPC(REL32),
	R_PPC(PLT32),
	R_PPC(PLTREL32),
	R_PPC(PLT16_LO),
	R_PPC(PLT16_HI),
	R_PPC(PLT16_HA),
	R_PPC(SDAREL16),
	R_PPC(SECTOFF),
	R_PPC(SECTOFF_LO),
	R_PPC(SECTOFF_HI),
	R_PPC(SECTOFF_HA),
	R_PPC(TLS),
	R_PPC(DTPMOD32),
	R_PPC(TPREL16),
	R_PPC(TPREL16_LO),
	R_PPC(TPREL16_HI),
	R_PPC(TPREL16_HA),
	R_PPC(TPREL32),
	R_PPC(DTPREL16),
	R_PPC(DTPREL16_LO),
	R_PPC(DTPREL16_HI),
	R_PPC(DTPREL16_HA),
	R_PPC(DTPREL32),
	R_PPC(GOT_TLSGD16),
	R_PPC(GOT_TLSGD16_LO),
	R_PPC(GOT_TLSGD16_HI),
	R_PPC(GOT_TLSGD16_HA),
	R_PPC(GOT_TLSLD16),
	R_PPC(GOT_TLSLD16_LO),
	R_PPC(GOT_TLSLD16_HI),
	R_PPC(GOT_TLSLD16_HA),
	R_PPC(GOT_TPREL16),
	R_PPC(GOT_TPREL16_LO),
	R_PPC(GOT_TPREL16_HI),
	R_PPC(GOT_TPREL16_HA),
	R_PPC(GOT_DTPREL16),
	R_PPC(GOT_DTPREL16_LO),
	R_PPC(GOT_DTPREL16_HI),
	R_PPC(GOT_DTPREL16_HA),
#if 0
	R_PPC(EMB_NADDR32),
	R_PPC(EMB_NADDR16),
	R_PPC(EMB_NADDR16_LO),
	R_PPC(EMB_NADDR16_HI),
	R_PPC(EMB_NADDR16_HA),
	R_PPC(EMB_SDAI16),
	R_PPC(EMB_SDA2I16),
	R_PPC(EMB_SDA2REL),
	R_PPC(EMB_SDA21),
	R_PPC(EMB_MRKREF),
	R_PPC(EMB_RELSEC16),
	R_PPC(EMB_RELST_LO),
	R_PPC(EMB_RELST_HI),
	R_PPC(EMB_RELST_HA),
	R_PPC(EMB_BIT_FLD),
	R_PPC(EMB_RELSDA),
	R_PPC(DIAB_SDA21_LO),
	R_PPC(DIAB_SDA21_HI),
	R_PPC(DIAB_SDA21_HA),
	R_PPC(DIAB_RELSDA_LO),
	R_PPC(DIAB_RELSDA_HI),
	R_PPC(DIAB_RELSDA_HA),
	R_PPC(REL16),
	R_PPC(REL16_LO),
	R_PPC(REL16_HI),
	R_PPC(REL16_HA),
	R_PPC(TOC16),
#endif
};

static const struct reloc_desc *lookup_reloc(unsigned reloc_val)
{
	const struct reloc_desc *rd;
	unsigned int i;

	for (rd = reloc_desc_tab, i = 0;
		i < sizeof(reloc_desc_tab)/sizeof(reloc_desc_tab[0]);
		i++, rd++)
		if (reloc_val == rd->val)
			return rd;

	return NULL;
}


void dump_reloc_entry_a(soinfo *si, Elf32_Rela *rela)
{
    unsigned type = ELF32_R_TYPE(rela->r_info);
    unsigned sym = ELF32_R_SYM(rela->r_info);
	unsigned offset = rela->r_offset;
	unsigned addend = rela->r_addend;
	const struct reloc_desc *rd;

	rd = lookup_reloc(type);
	if (rd == NULL)
	    ERROR("*Unknown 0x%02x sym 0x%06x offset 0x%08x addend 0x%08x\n", type, sym, offset, addend);
	else
	    ERROR("%-20s - sym 0x%06x offset 0x%08x addend 0x%08x\n", rd->text, sym, offset, addend);
}

void dump_sym_entry(soinfo *si, Elf32_Sym *sym)
{
    unsigned idx = sym - si->symtab;
	unsigned bind, type;

	bind = ELF32_ST_BIND(sym->st_info);
	type = ELF32_ST_TYPE(sym->st_info);
    ERROR("%d:%s 0x%08x (sz=%d info=0x%x other=0x%x) - bind=%x type=%x\n", idx, si->strtab + sym->st_name,
	    sym->st_value, sym->st_size, sym->st_info, sym->st_other, bind, type);
}

#endif

/* TODO: don't use unsigned for addrs below. It works, but is not
 * ideal. They should probably be either uint32_t, Elf32_Addr, or unsigned
 * long.
 */

void setup_got(soinfo *si)
{
    Elf32_Sym *symtab = si->symtab;
    const char *strtab;
    Elf32_Sym *s, *s2;
    char *sym_name;
    unsigned idx, *got, base, base2;
    extern unsigned ___resolve_stubs;

    /* Relocate the GOT.
    */
    DEBUG("%5d Setup GOT for %s (%p)\n", pid, si->name, si->plt_got);

    base = si->base;
    strtab = si->strtab;
    got = (unsigned *)(si->plt_got);

	/* must have the got to continue; */
    /* (missing GOT means not referencing other modules' symbols) */
	if (si->plt_got == NULL)
		return;

	si->pltresolve = si->plt_got;
	si->pltcall = si->pltresolve + PLT_CALL_OFFSET;
	si->pltinfo = si->pltresolve + PLT_INFO_OFFSET;
	si->first_rela = si->plt_got + PLT_1STRELA_OFFSET;

	if (si->plt_rel_count >= (2 << 12))
		si->plttable = (unsigned *) ((unsigned)si->first_rela + (2 * (2<<12) + 4 * (si->plt_rel_count - (2<<12))) * 4);
	else
		si->plttable = (unsigned *) ((unsigned)si->first_rela + (2 * si->plt_rel_count) * 4);

	si->pltinfo[0] = (unsigned)si->plttable;

	DEBUG("pltresolve = %p\n", si->pltresolve);
	DEBUG("pltcall = %p\n", si->pltcall);
	DEBUG("pltinfo = %p\n", si->pltinfo);
	DEBUG("plttable = %p\n", si->plttable);
	DEBUG("first_rela = %p\n", si->first_rela);
	DEBUG("plt_rel_count = %d (%d)\n", si->plt_rel_count, (si->plttable - si->first_rela) / 2);

	/* addis r11,r11,.PLTtable@ha*/
	si->pltcall[0] = ADDIS_R11_R11 | HA(si->plttable);
	/* lwz r11,plttable@l(r11) */
	si->pltcall[1] = LWZ_R11_R11 | L(si->plttable);
	si->pltcall[2] = MCTR_R11;	/* mtctr r11 */
	si->pltcall[3] = BCTR;	/* bctr */
	dcbf(&si->pltcall[0]);
	dcbf(&si->pltcall[3]);
}

void process_got(soinfo *si)
{
    Elf32_Sym *symtab = si->symtab;
    const char *strtab;
    Elf32_Sym *s, *s2;
    char *sym_name;
    unsigned idx, *got, base, base2;
    extern unsigned ___resolve_stubs;

    /* Relocate the GOT.
    */
    DEBUG("%5d Processing GOT for %s (%p)\n", pid, si->name, si->plt_got);

}

int reloc_plt_setup(soinfo *si)
{
	return 0;
}

int reloc_library(soinfo *si, unsigned int reltype, void *rels, unsigned count)
{
    Elf32_Rela *rela = rels;
    Elf32_Sym *symtab = si->symtab;
    const char *strtab = si->strtab;
    Elf32_Sym *s, *st, *scpy;
    unsigned base;
    unsigned *r_addr;
    Elf32_Rela *start;
    unsigned i, idx;
	unsigned val;
	unsigned target;
    unsigned loff, ooff, loffcpy;

    if (reltype != DT_RELA) {
        ERROR("%5d cannot relocate !DT_RELA in '%s'\n", pid, si->name);
        return -1;
    }

    start = rela;
    loff = si->base;

	DEBUG("%5d relocating %d entries\n", pid, count);

    for (i = 0; i < count; i++, rela++) {
        unsigned type, sym, reloc, sym_addr;
        const char *sym_name = NULL;

        if (ELF32_R_SYM(rela->r_info) == 0xffffff)
            continue;

        type = ELF32_R_TYPE(rela->r_info);

        sym = ELF32_R_SYM(rela->r_info);
        s = si->symtab + sym;
        sym_name = si->strtab + s->st_name;

		r_addr = (unsigned *)(rela->r_offset + si->base);
        DEBUG("%5d Processing '%s' relocation at index %d\n", pid, si->name, i);

        ooff = (unsigned)-1;
        st = NULL;
        /* no lookup */
        if (sym != 0 && !(ELF32_ST_BIND(s->st_info) == STB_LOCAL &&
                    (ELF32_ST_TYPE(s->st_info) == STT_NOTYPE ||
                        ELF32_ST_TYPE(s->st_info) == STT_SECTION))) {
            st = _do_lookup(si, sym_name, &base);
            if (st == NULL) {
                dump_reloc_entry_a(si, rela);
                dump_sym_entry(si, &symtab[sym]);
                ERROR("%5d cannot locate '%s' in '%s'\n", pid, sym_name, si->name);
                return -1;
            }
            COUNT_RELOC(RELOC_SYMBOL);
        }

		switch (type) {
		case R_PPC_RELATIVE:
			if (ELF32_ST_BIND(s->st_info) == STB_LOCAL &&
			    (ELF32_ST_TYPE(s->st_info) == STT_SECTION ||
			    ELF32_ST_TYPE(s->st_info) == STT_NOTYPE) ) {
				val = si->base + rela->r_addend;
            } else {
                    val = si->base + st->st_value + rela->r_addend;
            }

			*r_addr = val;

			break;

		case R_PPC_JMP_SLOT:
			target = base + st->st_value + rela->r_addend;
			val = target - (unsigned)r_addr;

			if (si->pltresolve == NULL) {
				ERROR("%5d R_PPC_JMP_SLOT without plt_got in '%s'\n", pid, si->name);
				return -1;
			}

			if (!B24_VALID_RANGE(val)) {
				/* if offset is > R_PPC_24 deal with it */
				idx = (r_addr - si->first_rela) >> 1;

				if (idx >= (2 << 12)) {
					/* addis r11,r11,.PLTtable@ha*/
					r_addr[0] = ADDIS_R11_R0 | HA(idx*4);
					r_addr[1] = ADDI_R11_R11 | L(idx*4);
					BR(r_addr[2], si->pltcall);
				} else {
					r_addr[0] = LI_R11 | (idx * 4);
					BR(r_addr[1], si->pltcall);
                }

				dcbf(&r_addr[0]);
				dcbf(&r_addr[2]);

				val = base + st->st_value + rela->r_addend;
				si->plttable[idx] = val;

			} else {
				/* if the offset is small enough,
				 * branch directly to the dest
				 */
				BR(r_addr[0], target);
				dcbf(&r_addr[0]);
            }
            break;

		case R_PPC_ADDR32:
			if (ELF32_ST_BIND(s->st_info) == STB_LOCAL &&
			    (ELF32_ST_TYPE(s->st_info) == STT_SECTION ||
			    ELF32_ST_TYPE(s->st_info) == STT_NOTYPE) ) {
				val = base + rela->r_addend;
			} else {
				val = base + st->st_value + rela->r_addend;
			}

            *r_addr = val;

            break;

		/* should not be supported ??? */
		case R_PPC_REL24:
			val = base + st->st_value + rela->r_addend - (unsigned)r_addr;

			if (!B24_VALID_RANGE(val)){
				ERROR("%5d R_PPC_REL24 invalid in '%s'\n", pid, si->name);
                return -1;
            }
			val &= ~0xfc000003;
			val |= (*r_addr & 0xfc000003);
			*r_addr = val;
			dcbf(r_addr);
            break;

		case R_PPC_ADDR16_LO:
			val = si->base + rela->r_addend;
			*(unsigned short *)r_addr = (unsigned short)val;
			dcbf(r_addr);
            break;

		case R_PPC_ADDR16_HI:
			val = si->base + rela->r_addend;
			*(unsigned short *)r_addr = (unsigned short)(val >> 16);
			dcbf(r_addr);
            break;

		case R_PPC_ADDR16_HA:
			val = si->base + rela->r_addend;
			*(Elf32_Half *)r_addr = ((val + 0x8000) >> 16);
			dcbf(r_addr);
            break;

		case R_PPC_REL14_BRTAKEN:
			/* val |= 1 << (31-10) XXX? */
		case R_PPC_REL14:
		case R_PPC_REL14_BRNTAKEN:
            val = base + st->st_value + rela->r_addend - (unsigned)r_addr;
			if (((val & 0xffff8000) != 0) && ((val & 0xffff8000) != 0xffff8000)) {
				ERROR("%5d R_PPC_REL14 invalid in '%s'\n", pid, si->name);
                return -1;
            }
			val &= ~0xffff0003;
			val |= (*r_addr & 0xffff0003);
			*r_addr = val;
			dcbf(r_addr);
			break;

		case R_PPC_GLOB_DAT:
			*r_addr = base + st->st_value + rela->r_addend;
			break;

		case R_PPC_COPY:
			/*
			 * we need to find a symbol, that is not in the current
			 * object, start looking at the beginning of the list,
			 * searching all objects but _not_ the current object,
			 * first one found wins.
			 */
            scpy = _do_lookup_non_local(si, sym_name, &base);
			if (scpy == NULL) {
                dump_reloc_entry_a(si, rela);
                dump_sym_entry(si, &symtab[sym]);
                ERROR("%5d cannot locate '%s' from '%s'\n", pid, sym_name, si->name);
                return -1;
            }
            if (st->st_size != scpy->st_size) {
                ERROR("%5d symbols size differ for %s in '%s'\n", pid, sym_name, si->name);
                return -1;
            }
            memcpy(r_addr, (void *)base + scpy->st_value, scpy->st_size);
			break;

		case R_PPC_NONE:
			break;

		default:
            dump_reloc_entry_a(si, rela);
            dump_sym_entry(si, &symtab[sym]);
			ERROR("%5d: %s: unsupported relocation '%s' %d at %p\n", pid,
			    si->name, sym_name,
			    ELF32_R_TYPE(rela->r_info), r_addr );
            return -1;
		}

    }
    return 0;
}
