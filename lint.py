#!/usr/bin/env python

"""
Lint script via clang-format.

Usage

    $ ./lint.py [fix]
"""

import sys
import os
import subprocess
import xml.etree.ElementTree as ET

FILE_EXTENSIONS = ('.h', '.c')
CLANGFOMART_NAMES = ['clang-format', 'clang-format-3.5', 'clang-format-3.6']
CLANGFORMAT_LINT_OPTIONS = ['-output-replacements-xml', '-style=file']
CLANGFORMAT_FIX_OPTIONS = ['-i', '-style=file']


def print_usage():
    print "Usage: ./lint.py [fix]"


def traverse_files():
    """Get file path list recursively.
    """
    paths = []
    for root, dirs, files in os.walk("./"):
        for filename in files:
            if filename.endswith(FILE_EXTENSIONS):
                paths.append(os.path.join(root, filename))
    return paths


def get_clang_format_bin():
    for name in CLANGFOMART_NAMES:
        try:
            subprocess.check_output([name, "-version"])
        except OSError:
            continue
        else:
            return name
    raise Exception("No clang-format command available.")


def lint(fix=False):
    num_errors = 0
    num_error_files = 0
    num_fixed_files = 0
    clangformat_bin = get_clang_format_bin()
    for path in traverse_files():
        cmd = [clangformat_bin, path]
        cmd.extend(CLANGFORMAT_LINT_OPTIONS)
        out = subprocess.check_output(cmd)
        root = ET.fromstring(out)
        has_error = False
        for tag in root.findall('replacement'):
            offset = tag.get('offset', None)
            length = tag.get("length", None)
            if offset is not None:
                has_error = True
                num_errors += 1
                print "{0}:{1},{2}".format(path, offset, length)
        if has_error:
            num_error_files += 1
        if fix:
            cmd = [clangformat_bin, path]
            cmd.extend(CLANGFORMAT_FIX_OPTIONS)
            if subprocess.call(cmd) == 0:
                num_fixed_files += 1
                if has_error:
                    print "{} fixed".format(path)
    if num_errors > 0 and num_error_files != num_fixed_files:
        sys.exit(1)


if __name__ == '__main__':
    if len(sys.argv) <= 1:  # Case ./program
        lint(fix=False)
    elif sys.argv[1] == 'fix':  # Case ./program fix
        lint(fix=True)
    else:
        print_usage()
