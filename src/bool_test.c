/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "test.h"
#include "bool.h"

void case_true();
void case_false();

int
main(int argc, const char *argv[])
{
    struct test_case cases[] = {
        {"test true", &case_true},
        {"test false", &case_false},
        {NULL, NULL},
    };

    run_cases(cases);
}

void
case_true()
{
    assert(true);
}

void
case_false()
{
    assert(!false);
}
