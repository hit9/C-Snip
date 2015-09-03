/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>

#include "utils.h"

struct test_case {
    const char  *name;    /* test case name */
    void        (*fn)();  /* test case function */
};

static void
run_cases(const char *name, struct test_case cases[])
{
    int idx = 0;

    while (1) {
        struct test_case c = cases[idx];

        if (c.name == NULL || c.fn == NULL)
            break;

        double start_at = time_now();
        (c.fn)();
        double end_at = time_now();
        idx += 1;
        printf("ok\t%s\t%s\t%.3fms\n", name, c.name,
                end_at - start_at);
    }
}
