#!/usr/bin/env python3
# Format project source code.

# ------------------------------------------------------------------------------

import glob
import subprocess
import os
import fnmatch
import sys

# ------------------------------------------------------------------------------

clang_format_exec = "/usr/bin/clang-format"

# ------------------------------------------------------------------------------


class srcfile(object):
    def __init__(self, name, formatter):
        self.name = name
        self.formatter = formatter

    def dfilter(self, dlist):
        """return true if the file is in a filtered directory"""
        for d in dlist:
            if self.name.startswith(d):
                return True
        return False

    def ffilter(self, flist):
        """return true if the file is filtered"""
        return self.name in flist

    def format(self):
        """format the file"""
        return self.formatter(self.name)


# ------------------------------------------------------------------------------


def exec_cmd(cmd):
    """execute a command, return the output and return code"""
    output = ""
    rc = 0
    try:
        output = subprocess.check_output(cmd, shell=True)
    except subprocess.CalledProcessError as x:
        rc = x.returncode
    return output, rc


# ------------------------------------------------------------------------------


def get_files(dlist, fo_flist, fo_dlist):
    # get the full file list
    flist = []
    for d, formatter in dlist:
        for root, dname, fnames in os.walk(d):
            for fname in fnmatch.filter(fnames, "*.[ch]"):
                flist.append(srcfile(os.path.join(root, fname), formatter))
            for fname in fnmatch.filter(fnames, "*.cc"):
                flist.append(srcfile(os.path.join(root, fname), formatter))
    # run the filters
    flist = [f for f in flist if not f.dfilter(fo_dlist)]
    flist = [f for f in flist if not f.ffilter(fo_flist)]
    return flist


# ------------------------------------------------------------------------------

fmt1_style = "{BasedOnStyle: Google, ColumnLimit: 120}"


def fmt1(fname):
    print("fmt1 on %s" % fname)
    exec_cmd('%s -i --style="%s" %s' % (clang_format_exec, fmt1_style, fname))


# ------------------------------------------------------------------------------

# *.c and *.h files in these directories will be auto-formatted.
src_dirs = (
    ("target/mb997", fmt1),
    ("app", fmt1),
    ("common", fmt1),
)

# don't format directories in this list
filter_dirs = ("common/rtt",)

# don't format files in this list
filter_files = ("target/mb997/stm32f4xx_hal_conf.h",)

# ------------------------------------------------------------------------------


def main():
    if len(sys.argv) == 2:
        f = srcfile(sys.argv[1], fmt1)
        f.format()
    else:
        flist = get_files(src_dirs, filter_files, filter_dirs)
        for f in flist:
            f.format()
    sys.exit(0)


main()

# ------------------------------------------------------------------------------
