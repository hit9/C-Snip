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


def lint(fix=False):
    num_errors = 0
    num_error_files = 0
    num_fixed_files = 0
    for path in traverse_files():
        cmd = ['clang-format', path]
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
            cmd = ['clang-format', path]
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
