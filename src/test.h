/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>

struct test_case {
    const char  *name;    /* test case name */
    void        (*fn)();  /* test case function */
};

static void
run_cases(const char *name, struct test_case cases[])
{
    int idx = 0;

    printf("[%s]\n", name);
    while (1) {
        struct test_case c = cases[idx];

        if (c.name == NULL || c.fn == NULL)
            break;

        (c.fn)();
        idx += 1;
        printf("  ok: %s\n", c.name);
    }
}
