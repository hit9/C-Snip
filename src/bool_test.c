/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "test.h"
#include "bool.h"

void case_bool_true();
void case_bool_false();

int
main(int argc, const char *argv[])
{
    struct test_case cases[] = {
        { "bool true", &case_bool_true },
        { "bool false", &case_bool_false },
        { NULL, NULL },
    };

    run_cases(cases);
}

void
case_bool_true()
{
    assert(true);
}

void
case_bool_false()
{
    assert(!false);
}
