#!/usr/bin/env python

"""
Lint script via clang-format.

Usage

    $ ./lint.py [fix] [BasedOnStyle=<google|llvm|chromium|mozilla|webkit>...]

Example

To lint with google style:

    $ ./lint.py BasedOnStyle=google

To use indent width as 2:

    $ ./lint.py IndentWidth=2

To fix lint errors in place:

    $ ./lint.py fix

Defaults

Default BasedOnStyle is google.
Default IndentWidth is 4.


"""

import sys
import os
import subprocess
import xml.etree.ElementTree as ET

FILE_EXTENSIONS = ('.h', '.c')

DEFAULT_CLANGFORMAT_STYLE_OPTIONS = {
    'BasedOnStyle': 'google',
    'IndentWidth': '4',
    'PointerAlignment': 'Right',
    'DerivePointerAlignment': 'false',
}


def print_usage():
    print """Usage:
      ./lint.py [fix] [<style-name>=<value>]
Examples
      To lint: ./lint.py
      To lint with style llvm: ./lint.py BasedOnStyle=google
      To fix lint errors in place: ./lint.py fix"""


def get_clangformat_style_options(args):
    """Get clangformat style options by command line args.
    """
    kvs = DEFAULT_CLANGFORMAT_STYLE_OPTIONS.copy()
    for arg in args:
        key, value = arg.split('=')
        kvs[key] = value
    pairs = []
    for key, value in kvs.items():
        pairs.append("{0}: {1}".format(key, value))
    if pairs:
        return "-style={{{0}}}".format(','.join(pairs))
    return None


def get_clangformat_lint_options(style_options):
    """Get clangformat full options by style options string for lint purpose.
    """
    options = ['-output-replacements-xml']
    if style_options is None:
        return options
    options.append(style_options)
    return options


def get_clangformat_fix_options(style_options):
    """Get clangformat full options by style options string for fix purpose.
    """
    options = ['-i']
    if style_options is None:
        return options
    options.append(style_options)
    return options


def traverse_files():
    """Get file path list recursively.
    """
    paths = []
    for root, dirs, files in os.walk("./"):
        for filename in files:
            if filename.endswith(FILE_EXTENSIONS):
                paths.append(os.path.join(root, filename))
    return paths


def lint(args, fix=False):
    num_errors = 0
    num_error_files = 0
    num_fixed_files = 0
    style_options = get_clangformat_style_options(args)
    for path in traverse_files():
        cmd = ['clang-format', path]
        cmd.extend(get_clangformat_lint_options(style_options))
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
            cmd.extend(get_clangformat_fix_options(style_options))
            if subprocess.call(cmd) == 0:
                num_fixed_files += 1
                if has_error:
                    print "{} fixed".format(path)
    if num_errors > 0 and num_error_files != num_fixed_files:
        sys.exit(1)


if __name__ == '__main__':
    if len(sys.argv) <= 1:  # Case ./program
        lint([], fix=False)
    elif sys.argv[1] == 'fix':  # Case ./program fix [pairs]
        lint(sys.argv[2:], fix=True)
    elif '=' in sys.argv[1]:  # Case ./program [pairs]
        lint(sys.argv[1:], fix=False)
    else:
        print_usage()
