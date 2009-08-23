#!/usr/bin/python
#
# this tool is used to check that the syscall numbers that are in
# SYSCALLS.TXT correspond to those found in the Linux kernel sources
# for the arm and i386 architectures
#

import sys, re, string, os, commands
from   bionic_utils import *

def usage():
    print "usage: checksyscalls [options] [kernel_headers_rootdir]"
    print "    options:    -v   enable verbose mode"
    sys.exit(1)


linux_root    = None

def parse_command_line(args):
    global linux_root, verbose

    program = args[0]
    args    = args[1:]
    D_setlevel(0)
    while len(args) > 0 and args[0][0] == "-":
        option = args[0][1:]
        args   = args[1:]

        if option == "v":
            D_setlevel(1)
        else:
            usage()

    if len(args) > 2:
        usage()

    if len(args) == 0:
        linux_root = find_kernel_headers()
        if linux_root == None:
            print "could not locate this system kernel headers root directory, please"
            print "specify one when calling this program, i.e. 'checksyscalls <headers-directory>'"
            sys.exit(1)
        print "using the following kernel headers root: '%s'" % linux_root
    else:
        linux_root = args[0]
        if not os.path.isdir(linux_root):
            print "the directory '%s' does not exist. aborting\n" % headers_root
            sys.exit(1)

parse_command_line(sys.argv)

# get the root Bionic directory, simply this script's dirname
#
bionic_root = find_bionic_root()
if not bionic_root:
    print "could not find the Bionic root directory. aborting"
    sys.exit(1)

if bionic_root[-1] != '/':
    bionic_root += "/"

class State:
    def __init__(self):
        self.syscalls = {}

        for arch in bionic_archs:
            self.syscalls[arch] = []

    # now read the Linux arm header
    def process_nr_line(self,line,dict):
        re_nr_line       = re.compile( r"#define __NR_(\w*)\s*\(__NR_SYSCALL_BASE\+\s*(\w*)\)" )
        re_nr_clock_line = re.compile( r"#define __NR_(\w*)\s*\(__NR_timer_create\+(\w*)\)" )
        re_arm_nr_line   = re.compile( r"#define __ARM_NR_(\w*)\s*\(__ARM_NR_BASE\+\s*(\w*)\)" )
        re_mips_line     = re.compile( r"#define __NR_(\w*)\s*\(__NR_Linux \+\s*(\w*)\)" )
        re_x86_line      = re.compile( r"#define __NR_(\w*)\s*([0-9]*)" )
        re_ppc_line      = re.compile( r"#define __NR_(\w*)\s*([0-9]*)" )

        m = re_nr_line.match(line)
        if m:
            dict[m.group(1)] = int(m.group(2))
            return

        m = re_nr_clock_line.match(line)
        if m:
            dict[m.group(1)] = int(m.group(2)) + 259
            return

        m = re_arm_nr_line.match(line)
        if m:
            #print "%s = %s" % (m.group(1), m.group(2))
            dict["ARM_"+m.group(1)] = int(m.group(2)) + 0x0f0000
            return

        m = re_mips_line.match(line)
        if m:
    	# MIPS has multiple ABIs defined in the unistd.h.  We only want
    	# the first o32 syscalls.  If we find it already in the object, just
    	# skip it.
            if not dict.has_key(m.group(1)):

            # try block because the ARM header has some #define _NR_XXXXX  /* nothing */
                try:
                    dict[m.group(1)] = int(m.group(2))
                    #print "%s = %s" % (m.group(1), m.group(2))
                except:
                    pass
                return

        m = re_x86_line.match(line)
        if m:
            # try block because the ARM header has some #define _NR_XXXXX  /* nothing */
            try:
                #print "%s = %s" % (m.group(1), m.group(2))
                dict[m.group(1)] = int(m.group(2))
            except:
                pass
            return

        m = re_ppc_line.match(line)
        if m:
            # try block because the ARM header has some #define _NR_XXXXX  /* nothing */
            try:
                #print "%s = %s" % (m.group(1), m.group(2))
                dict[m.group(1)] = int(m.group(2))
            except:
                pass
            return

    def process_header(self,header_file,dict):
        fp = open(header_file)
        D("reading "+header_file)
        for line in fp.xreadlines():
            line = line.strip()
            if not line: continue
            self.process_nr_line(line,dict)
        fp.close()

    def checksyscalls(self):
        global linux_root

        arm_dict = {}
        x86_dict = {}
        mips_dict = {}
        ppc_dict = {}

        # remove trailing slash and '/include' from the linux_root, if any
        if linux_root[-1] == '/':
            linux_root = linux_root[:-1]

        if len(linux_root) > 8 and linux_root[-8:] == '/include':
            linux_root = linux_root[:-8]

        arm_unistd = linux_root + "/arch/arm/include/asm/unistd.h"
        if not os.path.exists(arm_unistd):
            print "WEIRD: could not locate the ARM unistd.h header file"
            print "tried searching in '%s'" % arm_unistd
            print "maybe using a different set of kernel headers might help"
            sys.exit(1)

        # on recent kernels, asm-i386 and asm-x64_64 have been merged into asm-x86
        # with two distinct unistd_32.h and unistd_64.h definition files.
        # take care of this here
        #
        # We're only concerned with 32bit here.
        x86_unistd = linux_root + "/arch/x86/include/asm/unistd_32.h"
        if not os.path.exists(x86_unistd):
            print "WEIRD: could not locate the i386/x86 unistd.h header file"
            print "tried searching in '%s' and '%s'" % (x86_unistd1, x86_unistd)
            print "maybe using a different set of kernel headers might help"
            sys.exit(1)

        mips_unistd = linux_root + "/arch/mips/include/asm/unistd.h"
        if not os.path.exists(mips_unistd):
            print "WEIRD: could not locate the MIPS unistd.h header file"
            print "tried searching in '%s'" % mips_unistd
            print "maybe using a different set of kernel headers might help"
            sys.exit(1)

        ppc_unistd = linux_root + "/arch/powerpc/include/asm/unistd.h"
        if not os.path.exists(ppc_unistd):
            print "WEIRD: could not locate the PPC unistd.h header file"
            print "tried searching in '%s'" % ppc_unistd
            print "maybe using a different set of kernel headers might help"
            sys.exit(1)

        self.process_header( arm_unistd, arm_dict )
        self.process_header( x86_unistd, x86_dict )
        self.process_header( mips_unistd, mips_dict )
        self.process_header( ppc_unistd, ppc_dict )

        # now perform the comparison
        errors = 0
        for sc in self.syscalls["arm"]:
            sc_name = sc["name"]
            sc_id   = sc["id"]
            if sc_id >= 0:
                if not arm_dict.has_key(sc_name):
                    print "arm syscall %s not defined !!" % sc_name
                    errors += 1
                elif arm_dict[sc_name] != sc_id:
                    print "arm syscall %s should be %d instead of %d !!" % (sc_name, arm_dict[sc_name], sc_id)
                    errors += 1

        for sc in self.syscalls["x86"]:
            sc_name = sc["name"]
            sc_id  = sc["id"]
            if sc_id >= 0:
                if not x86_dict.has_key(sc_name):
                    print "x86 syscall %s not defined !!" % sc_name
                    errors += 1
                elif x86_dict[sc_name] != sc_id:
                    print "x86 syscall %s should be %d instead of %d !!" % (sc_name, x86_dict[sc_name], sc_id)
                    errors += 1

        for sc in self.syscalls["mips"]:
            sc_name = sc["name"]
            sc_id  = sc["id"]
            if sc_id >= 0:
                if not mips_dict.has_key(sc_name):
                    print "mips syscall %s not defined !!" % sc_name
                    errors += 1
                elif mips_dict[sc_name] != sc_id:
                    print "mips syscall %s should be %d instead of %d !!" % (sc_name, mips_dict[sc_name], sc_id)
                    errors += 1

        for sc in self.syscalls["ppc"]:
            sc_name = sc["name"]
            sc_id  = sc["id"]
            if sc_id >= 0:
                if not ppc_dict.has_key(sc_name):
                    print "ppc syscall %s not defined !!" % sc_name
                    errors += 1
                elif ppc_dict[sc_name] != sc_id:
                    print "ppc syscall %s should be %d instead of %d !!" % (sc_name, ppc_dict[sc_name], sc_id)
                    errors += 1


        if errors == 0:
            print "congratulations, everything's fine !!"
        else:
            print "correct %d errors !!" % errors

state = State()
process_syscalls_file(state, bionic_root+"SYSCALLS.TXT")
state.checksyscalls()
