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
    printf("======> %s <======\n", name);

    int idx = 0;

    while (1) {
        struct test_case c = cases[idx];

        if (c.name == NULL || c.fn == NULL)
            break;

        (c.fn)();
        idx += 1;
        printf("[%d] ok => %s\n", idx, c.name);
    }
}
