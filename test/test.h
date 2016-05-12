/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>

#include "datetime.h"

struct test_case {
    const char *name; /* test case name */
    void (*fn)();     /* test case function */
};

static void run_cases(const char *name, struct test_case cases[]);
