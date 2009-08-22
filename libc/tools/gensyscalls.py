#!/usr/bin/python
#
# this tool is used to generate the syscall assmbler templates
# to be placed into arch-x86/syscalls, as well as the content
# of arch-x86/linux/_syscalls.h
#

import sys, os.path, glob, re, commands, filecmp, shutil

from bionic_utils import *

# set this to 1 if you want to generate thumb stubs
gen_thumb_stubs = 0

# set this to 1 if you want to generate ARM EABI stubs
gen_eabi_stubs = 1

# get the root Bionic directory, simply this script's dirname
#
bionic_root = find_bionic_root()
if not bionic_root:
    print "could not find the Bionic root directory. aborting"
    sys.exit(1)

if bionic_root[-1] != '/':
    bionic_root += "/"

print "bionic_root is %s" % bionic_root

# temp directory where we store all intermediate files
bionic_temp = "/tmp/bionic_gensyscalls/"

# all architectures, update as you see fit
all_archs = [ "arm", "x86", "mips", "ppc" ]
arch_deftests = {
    "arm"  : "__arm__",
    "x86"  : "__i386__",
    "mips" : "__mips__",
    "ppc"  : "__powerpc__"
}
arch_syscall_base = {
    "x86"  : "0",
    "mips" : "4000",
    "ppc"  : "0"
}
#arch_codegen = {
#    "arm": lambda x: 
#            if gen_thumb_stubs:
#                frag = self.thumb_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
#            else:
#                if gen_eabi_stubs:
#                    frag = self.arm_eabi_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
#                else:
#                    frag = self.arm_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
#    "x86": lambda x:
#                syscall_cid = 
#                x.sc["cid"] >= 0 ?
#                    self.x86_genstub_cid(syscall_func, len(syscall_params), "__NR_"+x.sc["name"], x.sc["cid"])
#                else:
#                    frag = self.x86_genstub(syscall_func,len(syscall_params),"__NR_"+x.sc["name"])
#    "ppc": lambda x: x.ppc_genstub(syscall_func,len(x.sc["param"]),"__NR_"+x.sc["name"])
#}

def make_dir( path ):
    if not os.path.exists(path):
        parent = os.path.dirname(path)
        if parent:
            make_dir(parent)
        os.mkdir(path)

def create_file( relpath ):
    dir = os.path.dirname( bionic_temp + relpath )
    make_dir(dir)
    return open( bionic_temp + relpath, "w" )

# x86 assembler templates for each syscall stub
#

x86_header = """/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    .text
    .type %(fname)s, @function
    .globl %(fname)s
    .align 4

%(fname)s:
"""

x86_registers = [ "%ebx", "%ecx", "%edx", "%esi", "%edi", "%ebp" ]

x86_call = """    movl    $%(idname)s, %%eax
    int     $0x80
    cmpl    $-129, %%eax
    jb      1f
    negl    %%eax
    pushl   %%eax
    call    __set_errno
    addl    $4, %%esp
    orl     $-1, %%eax
1:
"""

x86_return = """    ret
"""

# ARM assembler templates for each syscall stub
#
arm_header = """/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    .text
    .type %(fname)s, #function
    .globl %(fname)s
    .align 4
    .fnstart

%(fname)s:
"""

arm_call_default = arm_header + """\
    swi   #%(idname)s
    movs    r0, r0
    bxpl    lr
    b       __set_syscall_errno
    .fnend
"""

arm_call_long = arm_header + """\
    .save   {r4, r5, lr}
    stmfd   sp!, {r4, r5, lr}
    ldr     r4, [sp, #12]
    ldr     r5, [sp, #16]
    swi     # %(idname)s
    ldmfd   sp!, {r4, r5, lr}
    movs    r0, r0
    bxpl    lr
    b       __set_syscall_errno
    .fnend
"""

arm_eabi_call_default = arm_header + """\
    .save   {r4, r7}
    stmfd   sp!, {r4, r7}
    ldr     r7, =%(idname)s
    swi     #0
    ldmfd   sp!, {r4, r7}
    movs    r0, r0
    bxpl    lr
    b       __set_syscall_errno
    .fnend
"""

arm_eabi_call_long = arm_header + """\
    mov     ip, sp
    .save   {r4, r5, r6, r7}
    stmfd   sp!, {r4, r5, r6, r7}
    ldmfd   ip, {r4, r5, r6}
    ldr     r7, =%(idname)s
    swi     #0
    ldmfd   sp!, {r4, r5, r6, r7}
    movs    r0, r0
    bxpl    lr
    b       __set_syscall_errno
    .fnend
"""

# ARM thumb assembler templates for each syscall stub
#
thumb_header = """/* autogenerated by gensyscalls.py */
    .text
    .type %(fname)s, #function
    .globl %(fname)s
    .align 4
    .thumb_func
    .fnstart

#define  __thumb__
#include <sys/linux-syscalls.h>


%(fname)s:
"""

thumb_call_default = thumb_header + """\
    .save   {r7,lr}
    push    {r7,lr}
    ldr     r7, =%(idname)s
    swi     #0
    tst     r0, r0
    bmi     1f
    pop     {r7,pc}
1:
    neg     r0, r0
    ldr     r1, =__set_errno
    blx     r1
    pop     {r7,pc}
    .fnend
"""

thumb_call_long = thumb_header + """\
    .save  {r4,r5,r7,lr}
    push   {r4,r5,r7,lr}
    ldr    r4, [sp,#16]
    ldr    r5, [sp,#20]
    ldr    r7, =%(idname)s
    swi    #0
    tst    r0, r0
    bmi    1f
    pop    {r4,r5,r7,pc}
1:
    neg    r0, r0
    ldr    r1, =__set_errno
    blx    r1
    pop    {r4,r5,r7,pc}
    .fnend
"""

# MIPS assembler templates for each syscall stub
#
mips_header = """/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>
#include <sys/regdef.h>

    .text
    .globl %(fname)s
    .align 2
    .ent %(fname)s,0

%(fname)s:
"""

mips_call = mips_header + """\
    .set noreorder

    .cpload t9
    li v0, %(idname)s
    syscall
    .set reorder
    bne a3, zero, err
    nop
    j ra
    nop
err:
    subu a0, zero, v0
#ifdef __PIC__
    la t9, __set_syscall_errno
    jr t9
#else
    j       __set_syscall_errno
#endif
    nop
    .end %(fname)s
    .size %(fname)s,.-%(fname)s
"""

# PPC assembler templates for each syscall stub
#
ppc_header = """/* autogenerated by gensyscalls.py */
#include <sys/linux-syscalls.h>

    /* == PPC HEADER == */
    .text
    .globl %(fname)s
    .type %(fname)s,@function
    .align 4

%(fname)s:
"""

ppc_call = """\
    li  0, %(idname)s
    sc
    bnslr+
    b   __set_syscall_errno
    .size %(fname)s,.-%(fname)s
"""


class State:
    def __init__(self):
        self.old_stubs = []
        self.new_stubs = []
        self.other_files = []
        self.syscalls = {}

        for arch in all_archs:
            self.syscalls[arch] = []

    def x86_genstub(self, fname, numparams, idname):
        t = { "fname"  : fname,
              "idname" : idname }

        result     = x86_header % t
        stack_bias = 4
        for r in range(numparams):
            result     += "    pushl   " + x86_registers[r] + "\n"
            stack_bias += 4

        for r in range(numparams):
            result += "    mov     %d(%%esp), %s" % (stack_bias+r*4, x86_registers[r]) + "\n"

        result += x86_call % t

        for r in range(numparams):
            result += "    popl    " + x86_registers[numparams-r-1] + "\n"

        result += x86_return
        return result

    def x86_genstub_cid(self, fname, numparams, idname, cid):
        # We'll ignore numparams here because in reality, if there is a
        # dispatch call (like a socketcall syscall) there are actually
        # only 2 arguments to the syscall and 2 regs we have to save:
        #   %ebx <--- Argument 1 - The call id of the needed vectored
        #                          syscall (socket, bind, recv, etc)
        #   %ecx <--- Argument 2 - Pointer to the rest of the arguments
        #                          from the original function called (socket())
        t = { "fname"  : fname,
              "idname" : idname }

        result = x86_header % t
        stack_bias = 4

        # save the regs we need
        result += "    pushl   %ebx" + "\n"
        stack_bias += 4
        result += "    pushl   %ecx" + "\n"
        stack_bias += 4

        # set the call id (%ebx)
        result += "    mov     $%d, %%ebx" % (cid) + "\n"

        # set the pointer to the rest of the args into %ecx
        result += "    mov     %esp, %ecx" + "\n"
        result += "    addl    $%d, %%ecx" % (stack_bias) + "\n"

        # now do the syscall code itself
        result += x86_call % t

        # now restore the saved regs
        result += "    popl    %ecx" + "\n"
        result += "    popl    %ebx" + "\n"

        # epilog
        result += x86_return
        return result

    def arm_genstub(self,fname, flags, idname):
        t = { "fname"  : fname,
              "idname" : idname }
        if flags:
            numargs = int(flags)
            if numargs > 4:
                return arm_call_long % t
        return arm_call_default % t


    def arm_eabi_genstub(self,fname, flags, idname):
        t = { "fname"  : fname,
              "idname" : idname }
        if flags:
            numargs = int(flags)
            if numargs > 4:
                return arm_eabi_call_long % t
        return arm_eabi_call_default % t


    def thumb_genstub(self,fname, flags, idname):
        t = { "fname"  : fname,
              "idname" : idname }
        if flags:
            numargs = int(flags)
            if numargs > 4:
                return thumb_call_long % t
        return thumb_call_default % t

    def mips_genstub(self,fname, flags, idname):
        t = { "fname"  : fname,
              "idname" : idname }
        return mips_call % t

    def ppc_genstub_cid(self, fname, numparams, idname, cid):
        t = { "fname"  : fname,
              "idname" : idname }

        if numparams > 6:
            print "Maximum number of parameters of a mux syscall is 6"
            sys.exit(1)

        result = ppc_header % t
        space = (1 + numparams) * 4
        space = (space + 15) & ~15
        result += "    /* == SAVE %d (%d params) == */\n" % (space, numparams)

        # result += "    mflr 0\n"
        # result += "    stwu 1,-%d(1)\n" % space
        result += "    addi 1,1,-%d\n" % space
        # result += "    stw 0,%d(1)\n"  % (space + 4)
        for i in range(numparams):
            result += "    stw  %d,%d(1)\n" % (3 + i, space - (numparams - i) * 4)
        result += "    li 3,%d\n" % cid
        result += "    addi 4,1,%d\n" % (space - (numparams) * 4)

        # now do the syscall code itself
        result += "    li 0, %(idname)s\n" % t
        result += "    sc\n"
        # result += "    lwz 0,%d(1)\n" % (space + 4)
        result += "    addi 1,1,%d\n" % space
        # result += "    mtlr 0\n"
        result += "    bnslr+\n"
        result += "    b  __set_syscall_errno\n"
        result += "    .size %(fname)s,.-%(fname)s\n" % t

        return result

    def ppc_genstub(self,fname, flags, idname):
        t = { "fname"  : fname,
              "idname" : idname }
        result  = ppc_header % t
        result += ppc_call % t
        return result

    def process_file(self,input):

        # parse syscall.txt for every arch
        for arch in all_archs:
            D( "")
            D( ">>> processing architecture "+arch)
            parser = SysCallsTxtParser()
            parser.parse_file(input, arch)
            self.syscalls[arch] = parser.syscalls
            parser = None
    
        return

    def gen_NR_syscall(self,fp,name,id):
        fp.write( "#define __NR_%-25s    (__NR_SYSCALL_BASE + %d)\n" % (name,id) )

    # now dump the content of linux/_syscalls.h
    # this used to be very clever with trying to generate "common" and then
    # port specific syscall numbers.  The addition of more ports caused the
    # "common" list to shrink very small, and increased the complexity of
    # trying to determine what is common and not.  Now, just dump the whole
    # list for each port separately.
    def gen_linux_syscalls_h(self):
        path = "include/sys/linux-syscalls.h"
        D( "generating "+path )
        fp = create_file( path )
        fp.write( "/* auto-generated by gensyscalls.py, do not touch */\n" )
        fp.write( "#ifndef _BIONIC_LINUX_SYSCALLS_H_\n\n" )
        fp.write( "#if !defined __ASM_ARM_UNISTD_H && !defined __ASM_I386_UNISTD_H && !defined __ASM_POWERPC_UNISTD_H && !defined __ASM_MIPS_UNISTD_H\n" )

        # arm syscalls
        fp.write( "\n#if defined __arm__\n" )
        fp.write( "#if !defined __ARM_EABI__ && !defined __thumb__\n" )
        fp.write( "  #  define __NR_SYSCALL_BASE  0x900000\n" )
        fp.write( "  #else\n" )
        fp.write( "  #  define  __NR_SYSCALL_BASE  0\n" )
        fp.write( "  #endif\n" )
        fp.write( "#endif\n" )

        # only the arch specific syscalls are generated
        gen_syscalls = {}
        for sc in self.syscalls["arm"]:
            sc_id  = sc["id"]
            sc_name = sc["name"]
            sc_common = sc["common"]
            if sc_id >= 0 and sc_common and sc_name not in gen_syscalls:
                self.gen_NR_syscall( fp, sc_name, sc_id )
                gen_syscalls[sc_name] = True

        # arch specific syscalls
        for arch in all_archs:
            fp.write( "\n#ifdef "+arch_deftests[arch]+"\n" );

            # ARM is special and is handled above.
            if arch != "arm":
                fp.write( "#define __NR_SYSCALL_BASE "+arch_syscall_base[arch]+"\n" );
            for sc in self.syscalls[arch]:
                sc_id  = sc["id"]
                sc_name = sc["name"]
                if sc_id >= 0 and sc_name not in gen_syscalls:
                    self.gen_NR_syscall( fp, sc_name, sc_id )
            fp.write( "#endif\n" )

        fp.write( "\n#endif /* __ASM_XXX_UNISTD_H */\n" )
        fp.write( "\n#endif /* _BIONIC_LINUX_SYSCALLS_H_ */\n" )
        fp.close()
        self.other_files.append( path )

    # now dump the content of linux/_syscalls.h
    def gen_linux_unistd_h(self):
        path = "include/sys/linux-unistd.h"
        D( "generating "+path )
        fp = create_file( path )
        fp.write( "/* auto-generated by gensyscalls.py, do not touch */\n" )
        fp.write( "#ifndef _BIONIC_LINUX_UNISTD_H_\n\n" );
        fp.write( "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n" )

        # common syscalls are generated
        gen_decls = {}
        for sc in self.syscalls["arm"]:
            sc_id  = sc["id"]
            sc_name = sc["name"]
            sc_common = sc["common"]
            print "\t"+sc["name"]
            if sc_id >= 0 and sc_common and sc_name not in gen_decls:
                fp.write( sc["decl"]+"\n" )
                gen_decls[sc_name] = True

        # arch specific syscalls are generated
        for arch in all_archs:
            fp.write( "\n#ifdef "+arch_deftests[arch]+"\n" );
            for sc in self.syscalls[arch]:
                sc_id  = sc["id"]
                sc_name = sc["name"]
                if sc_id >= 0 and sc_name not in gen_decls:
                    fp.write( sc["decl"]+"\n" )
            fp.write( "#endif\n" )

        fp.write( "#ifdef __cplusplus\n}\n#endif\n" )
        fp.write( "\n#endif /* _BIONIC_LINUX_UNISTD_H_ */\n" );
        fp.close()
        self.other_files.append( path )

    # now dump the contents of syscalls.mk
    def gen_arch_syscalls_mk(self, arch):
        path = "arch-%s/syscalls.mk" % arch
        D( "generating "+path )
        fp = create_file( path )
        fp.write( "# auto-generated by gensyscalls.py, do not touch\n" )
        fp.write( "syscall_src := \n" )

        for sc in self.syscalls[arch]:
            if sc["id"] >= 0:
                fp.write("syscall_src += arch-%s/syscalls/%s.S\n" %
                         (arch, sc["func"]))
        fp.close()
        self.other_files.append( path )

    # now generate each syscall stub
    def gen_syscall_stubs(self,arch):
        for sc in self.syscalls[arch]:
            fname = "arch-"+arch+"/syscalls/%s.S" % sc["func"]
            D( ">>> generating "+fname)

            syscall_func   = sc["func"]
            syscall_params = sc["params"]
            syscall_name   = sc["name"]
            syscall_id     = sc["id"]

            if arch == "arm":
                if gen_thumb_stubs:
                    frag = self.thumb_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
                else:
                    if gen_eabi_stubs:
                        frag = self.arm_eabi_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
                    else:
                        frag = self.arm_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
            elif arch == "x86":
                syscall_cid = sc["cid"]
                if syscall_cid >= 0:
                    frag = self.x86_genstub_cid(syscall_func, len(syscall_params), "__NR_"+syscall_name, syscall_cid)
                else:
                    frag = self.x86_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
            elif arch == "mips":
                    frag = self.mips_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)
            elif arch == "ppc":
                syscall_cid = sc["cid"]
                if syscall_cid >= 0:
                    frag = self.ppc_genstub_cid(syscall_func, len(syscall_params), "__NR_"+syscall_name, syscall_cid)
                else:
                    frag = self.ppc_genstub(syscall_func,len(syscall_params),"__NR_"+syscall_name)

            fp = create_file( fname )
            fp.write(frag)
            fp.close()
            self.new_stubs.append( fname )

    def  regenerate(self):
        D( "scanning for existing architecture-specific stub files" )

        bionic_root_len = len(bionic_root)

        for arch in all_archs:
            arch_path = bionic_root + "arch-" + arch
            D( "scanning " + arch_path )
            files = glob.glob( arch_path + "/syscalls/*.S" )
            for f in files:
                self.old_stubs.append( f[bionic_root_len:] )

        D( "found %d stub files" % len(self.old_stubs) )

        if not os.path.exists( bionic_temp ):
            D( "creating %s" % bionic_temp )
            os.mkdir( bionic_temp )

#        D( "p4 editing source files" )
#        for arch in all_archs:
#            commands.getoutput( "p4 edit " + arch + "/syscalls/*.S " )
#            commands.getoutput( "p4 edit " + arch + "/syscalls.mk" )
#        commands.getoutput( "p4 edit " + bionic_root + "include/sys/linux-syscalls.h" )

        D( "re-generating stubs and support files" )

        D( "re-generating common arch files" )
        self.gen_linux_syscalls_h()
        self.gen_linux_unistd_h()

        for arch in all_archs:
            D( "re-generating arch files for "+arch)
            self.gen_arch_syscalls_mk(arch)
            self.gen_syscall_stubs(arch)
            print "\n"

        D( "comparing files" )
        adds    = []
        edits   = []

        for stub in self.new_stubs + self.other_files:
            if not os.path.exists( bionic_root + stub ):
                # new file, P4 add it
                D( "new file:     " + stub)
                adds.append( bionic_root + stub )
                shutil.copyfile( bionic_temp + stub, bionic_root + stub )

            elif not filecmp.cmp( bionic_temp + stub, bionic_root + stub ):
                D( "changed file: " + stub)
                edits.append( stub )

        deletes = []
        for stub in self.old_stubs:
            if not stub in self.new_stubs:
                D( "deleted file: " + stub)
                deletes.append( bionic_root + stub )


        if adds:
            commands.getoutput("p4 add " + " ".join(adds))
        if deletes:
            commands.getoutput("p4 delete " + " ".join(deletes))
        if edits:
            commands.getoutput("p4 edit " +
                               " ".join((bionic_root + file) for file in edits))
            for file in edits:
                shutil.copyfile( bionic_temp + file, bionic_root + file )

        D("ready to go !!")

D_setlevel(1)

state = State()
state.process_file(bionic_root+"SYSCALLS.TXT")
state.regenerate()
