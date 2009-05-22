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

/* >>> IMPORTANT NOTE - READ ME BEFORE MODIFYING <<<
 *
 * Do NOT use malloc() and friends or pthread_*() code here.
 * Don't use printf() either; it's caused mysterious memory
 * corruption in the past.
 * The linker runs before we bring up libc and it's easiest
 * to make sure it does not depend on any complex libc features
 *
 */

unsigned _stub_helper(int sym, unsigned *got)
{
    soinfo *si;
    Elf32_Sym *symtab;
    const char *strtab;
    Elf32_Sym *s;
    char *sym_name;
    unsigned base;

    si = (soinfo *)(got[1]);
    symtab = si->symtab;
    strtab = si->strtab;

    sym_name = (char *)(strtab + symtab[sym].st_name);
    s = _do_lookup(NULL, sym_name, &base);
    if(s == 0) {
	ERROR("%5d cannot locate '%s'...\n", pid, sym_name);
    }
    else {
        DEBUG("Syn %s, Base %08x, value %08x\n", sym_name, base, s->st_value);
    }

    *(got + (sym+2)) = base + s->st_value;

    return base + s->st_value;
}

/* TODO: don't use unsigned for addrs below. It works, but is not
 * ideal. They should probably be either uint32_t, Elf32_Addr, or unsigned
 * long.
 */
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
    DEBUG("%5d Processing GOT, off %08x, base %08x, loc %04x, got %04x, tabno %08x\n", pid,
    si->plt_got, si->base, si->mips_gotlocnum, si->mips_gotsym, si->mips_symtabno);

    base = si->base;
    strtab = si->strtab;
    got = (unsigned *)(si->plt_got);

    /* First two entries are reserved for stub helpers.
    */
    *got++ = &___resolve_stubs;
    *got++ = (unsigned)si;
    idx = 2;
    while (idx++ < si->mips_gotlocnum)
    	*got++ += base;			/* Process Local GOTs */

    /* Process global GOTs.
    */
    idx = si->mips_gotsym;
    s = symtab + idx;
    while (idx++ < si->mips_symtabno) {
        sym_name = (char *)(strtab + s->st_name);
        DEBUG("GOT %s sym %d, shndx %d, info %d, val %08x, other %d\n", sym_name, idx, s->st_shndx, s->st_info, s->st_value, s->st_other);
	if (s->st_shndx == SHN_UNDEF || s->st_shndx == SHN_COMMON) {
            s2 = _do_lookup(si, sym_name, &base2);
            DEBUG("    shndx %d, info %d, val %08x, base %08x, other %d\n", s2->st_shndx, s2->st_info, s2->st_value, base2, s2->st_other);
	    *got = base2 + s2->st_value;
	}
	else if (((s->st_info & 0x0f) == STT_FUNC) && (*got != s->st_value))
	    *got += base;
	else if ((s->st_info & 0x0f) == STT_SECTION) {
	    if (s->st_other == 0)
	    	*got += base;
	}
	else
	    *got = base + s->st_value;
	got++;
	s++;
    }
}

int reloc_library(soinfo *si, Elf32_Rel *rel, unsigned count)
{
    Elf32_Sym *symtab = si->symtab;
    const char *strtab = si->strtab;
    Elf32_Sym *s;
    unsigned base;
    Elf32_Rel *start = rel;
    unsigned idx;

    for (idx = 0; idx < count; ++idx) {
        unsigned type = ELF32_R_TYPE(rel->r_info);
        unsigned sym = ELF32_R_SYM(rel->r_info);
        unsigned reloc = (unsigned)(rel->r_offset + si->base);
        unsigned sym_addr = 0;
        char *sym_name = NULL;

        DEBUG("%5d Processing '%s' relocation at index %d\n", pid,
              si->name, idx);
        if(sym != 0) {
            s = _do_lookup(si, strtab + symtab[sym].st_name, &base);
            if(s == 0) {
                ERROR("%5d cannot locate '%s'...\n", pid, sym_name);
                return -1;
            }
#if 0
            if((base == 0) && (si->base != 0)){
                    /* linking from libraries to main image is bad */
                ERROR("%5d cannot locate '%s'...\n", 
                       pid, strtab + symtab[sym].st_name);
                return -1;
            }
#endif

           if((ELF32_ST_BIND(s->st_info) != STB_WEAK) &&
              (s->st_shndx == SHN_UNDEF) && (s->st_value != 0)) {
                ERROR("%5d In '%s', shndx=%d && value=0x%08x name=%s. We do"
                     "not handle this yet\n",
                     pid, si->name, s->st_shndx, s->st_value,
                     strtab + symtab[sym].st_name);
                return -1;
            }
            sym_addr = (unsigned)(s->st_value + base);
            sym_name = (char *)(strtab + symtab[sym].st_name);
            COUNT_RELOC(RELOC_SYMBOL);
        } else {
            s = 0;
        }

        switch(type) {
        case R_MIPS_REL32:
            COUNT_RELOC(RELOC_RELATIVE);
            MARK(rel->r_offset);
            if(sym) {
                TRACE_TYPE(RELO, "%5d RELO ABS %08x (%08x) <- +%08x\n",
		        pid, reloc, *((unsigned *)reloc), sym_addr);
                *((unsigned*)reloc) = sym_addr;
            }
	    else {
                TRACE_TYPE(RELO, "%5d RELO RELATIVE %08x (%08x) <- +%08x\n",
		        pid, reloc, *((unsigned *)reloc), si->base);
                *((unsigned*)reloc) += si->base;
	    }
            break;
        case R_MIPS_NONE:
            break;

        default:
            ERROR("%5d unknown reloc type %d @ %p (%d)\n",
                  pid, type, rel, (int) (rel - start));
            return -1;
        }
        rel++;
    }

    return 0;
}

