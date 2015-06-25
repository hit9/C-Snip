/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>

#ifdef __linux
#include <mcheck.h>
#endif

struct test_case {
    const char *name;
    void (*fn)();
};

static void
run_cases(struct test_case cases[])
{
#ifdef __linux
    mtrace();
#endif

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
