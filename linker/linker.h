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

#ifndef _LINKER_H_
#define _LINKER_H_

#include <unistd.h>
#include <sys/types.h>
#include <linux/elf.h>

#undef PAGE_MASK
#undef PAGE_SIZE
#define PAGE_SIZE 4096
#define PAGE_MASK 4095

void debugger_init();
const char *addr_to_name(unsigned addr);

/* magic shared structures that GDB knows about */

struct link_map
{
    uintptr_t l_addr;
    char * l_name;
    uintptr_t l_ld;
    struct link_map * l_next;
    struct link_map * l_prev;
};

/* needed for dl_iterate_phdr to be passed to the callbacks provided */
struct dl_phdr_info
{
    Elf32_Addr dlpi_addr;
    const char *dlpi_name;
    const Elf32_Phdr *dlpi_phdr;
    Elf32_Half dlpi_phnum;
};


// Values for r_debug->state
enum {
    RT_CONSISTENT,
    RT_ADD,
    RT_DELETE
};

struct r_debug
{
    int32_t r_version;
    struct link_map * r_map;
    void (*r_brk)(void);
    int32_t r_state;
    uintptr_t r_ldbase;
};

typedef struct soinfo soinfo;

#define FLAG_LINKED     0x00000001
#define FLAG_ERROR      0x00000002
#define FLAG_EXE        0x00000004 // The main executable
#define FLAG_PRELINKED  0x00000008 // This is a pre-linked lib

#define SOINFO_NAME_LEN 128

struct soinfo
{
    const char name[SOINFO_NAME_LEN];
    Elf32_Phdr *phdr;
    int phnum;
    unsigned entry;
    unsigned base;
    unsigned size;
    // buddy-allocator index, negative for prelinked libraries
    int ba_index;

    unsigned *dynamic;

    unsigned wrprotect_start;
    unsigned wrprotect_end;

    soinfo *next;
    unsigned flags;

    const char *strtab;
    Elf32_Sym *symtab;
    unsigned sym_ent;

    unsigned nbucket;
    unsigned nchain;
    unsigned *bucket;
    unsigned *chain;

    unsigned *plt_got;

	unsigned plt_type;
	union {
		Elf32_Rel *rel;
		Elf32_Rela *rela;
		void *rel_any;
	} plt;
    unsigned plt_rel_sz;
    unsigned plt_rel_ent;
    unsigned plt_rel_count;

    Elf32_Rel *rel;
    unsigned rel_sz;
    unsigned rel_ent;
    unsigned rel_count;

    /* RELA */
    Elf32_Rela *rela;
    unsigned rela_sz;
    unsigned rela_ent;
    unsigned rela_count;

    unsigned *preinit_array;
    unsigned preinit_array_count;

    unsigned *init_array;
    unsigned init_array_count;
    unsigned *fini_array;
    unsigned fini_array_count;

    void (*init_func)(void);
    void (*fini_func)(void);

#ifdef ANDROID_ARM_LINKER
    /* ARM EABI section used for stack unwinding. */
    unsigned *ARM_exidx;
    unsigned ARM_exidx_count;
#endif

#ifdef ANDROID_MIPS_LINKER
	/* Information for GOT relocating. */
	unsigned mips_gotlocnum;
	unsigned mips_gotsym;
	unsigned mips_symtabno;
#endif

#ifdef ANDROID_PPC_LINKER
	unsigned ppc_got;
	unsigned *pltresolve;
	unsigned *pltcall;
	unsigned *pltinfo;
	unsigned *first_rela;
	unsigned *plttable;
#endif

    unsigned refcount;
    struct link_map linkmap;
};


extern soinfo libdl_info;
extern int debug_verbosity;
extern int pid;
extern Elf32_Sym *_do_lookup_in_so(soinfo *si, const char *name,
							unsigned *elf_hash);
extern Elf32_Sym * _do_lookup(soinfo *user_si, const char *name,
							unsigned *base);
extern Elf32_Sym * _do_lookup_non_local(soinfo *user_si, const char *name,
							unsigned *base);

#ifdef __mips__
#define LIBBASE 0x40000000
#define LIBLAST 0x50000000
#else
#define LIBBASE 0x80000000
#define LIBLAST 0x90000000
#endif
#define LIBINC  0x00100000


#ifdef ANDROID_ARM_LINKER

#define R_ARM_COPY       20
#define R_ARM_GLOB_DAT   21
#define R_ARM_JUMP_SLOT  22
#define R_ARM_RELATIVE   23

#elif defined(ANDROID_X86_LINKER)

#define R_386_32         1
#define R_386_PC32       2
#define R_386_GLOB_DAT   6
#define R_386_JUMP_SLOT  7
#define R_386_RELATIVE   8

#elif defined(ANDROID_MIPS_LINKER)

#define R_MIPS_REL32	3

#elif defined(ANROID_PPC_LINKER)

/* PowerPC relocations defined by the ABIs */
/* XXX don't know how many are used yet */
#define R_PPC_NONE		0
#define R_PPC_ADDR32		1	/* 32bit absolute address */
#define R_PPC_ADDR24		2	/* 26bit address, 2 bits ignored.  */
#define R_PPC_ADDR16		3	/* 16bit absolute address */
#define R_PPC_ADDR16_LO		4	/* lower 16bit of absolute address */
#define R_PPC_ADDR16_HI		5	/* high 16bit of absolute address */
#define R_PPC_ADDR16_HA		6	/* adjusted high 16bit */
#define R_PPC_ADDR14		7	/* 16bit address, 2 bits ignored */
#define R_PPC_ADDR14_BRTAKEN	8
#define R_PPC_ADDR14_BRNTAKEN	9
#define R_PPC_REL24		10	/* PC relative 26 bit */
#define R_PPC_REL14		11	/* PC relative 16 bit */
#define R_PPC_REL14_BRTAKEN	12
#define R_PPC_REL14_BRNTAKEN	13
#define R_PPC_GOT16		14
#define R_PPC_GOT16_LO		15
#define R_PPC_GOT16_HI		16
#define R_PPC_GOT16_HA		17
#define R_PPC_PLTREL24		18
#define R_PPC_COPY		19
#define R_PPC_GLOB_DAT		20
#define R_PPC_JMP_SLOT		21
#define R_PPC_RELATIVE		22
#define R_PPC_LOCAL24PC		23
#define R_PPC_UADDR32		24
#define R_PPC_UADDR16		25
#define R_PPC_REL32		26
#define R_PPC_PLT32		27
#define R_PPC_PLTREL32		28
#define R_PPC_PLT16_LO		29
#define R_PPC_PLT16_HI		30
#define R_PPC_PLT16_HA		31
#define R_PPC_SDAREL16		32
#define R_PPC_SECTOFF		33
#define R_PPC_SECTOFF_LO	34
#define R_PPC_SECTOFF_HI	35
#define R_PPC_SECTOFF_HA	36

#endif /* ANDROID_*_LINKER */


#ifndef DT_INIT_ARRAY
#define DT_INIT_ARRAY      25
#endif

#ifndef DT_FINI_ARRAY
#define DT_FINI_ARRAY      26
#endif

#ifndef DT_INIT_ARRAYSZ
#define DT_INIT_ARRAYSZ    27
#endif

#ifndef DT_FINI_ARRAYSZ
#define DT_FINI_ARRAYSZ    28
#endif

#ifndef DT_PREINIT_ARRAY
#define DT_PREINIT_ARRAY   32
#endif

#ifndef DT_PREINIT_ARRAYSZ
#define DT_PREINIT_ARRAYSZ 33
#endif

/* in theory we only need the above relative relocations,
   but in practice the following one turns up from time
   to time.  fushigi na.
*/
#define R_ARM_ABS32      2

/* define architecture relation type (DT_REL or DT_RELA) */
#if !defined(ANDROID_PPC_LINKER)
#define ANDROID_LINKER_ARCH_DEFAULT_RELTYPE  DT_REL
#else
#define ANDROID_LINKER_ARCH_DEFAULT_RELTYPE  DT_RELA
#endif

soinfo *find_library(const char *name);
unsigned unload_library(soinfo *si);
Elf32_Sym *lookup_in_library(soinfo *si, const char *name);
Elf32_Sym *lookup(const char *name, unsigned *base);
const char *linker_get_error(void);

#ifdef ANDROID_ARM_LINKER 
typedef long unsigned int *_Unwind_Ptr;
_Unwind_Ptr dl_unwind_find_exidx(_Unwind_Ptr pc, int *pcount);
#elif defined(ANDROID_X86_LINKER) || defined(ANDROID_MIPS_LINKER) || \
        defined(ANDROID_PPC_LINKER)
int dl_iterate_phdr(int (*cb)(struct dl_phdr_info *, size_t, void *), void *);
#endif

#if defined(ANDROID_MIPS_LINKER) || defined(ANDROID_PPC_LINKER)
void setup_got(soinfo *si);
void process_got(soinfo *si);
#endif

int reloc_library(soinfo *si, unsigned reltype, void *rels, unsigned count);

#endif
