/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "test.h"
#include "string.h"

void case_string_is_empty();

int
main(int argc, const char *argv[])
{
    struct test_case cases[] = {
        { "test string_is_empty", &case_string_is_empty },
        { NULL, NULL },
    };

    run_cases(cases);
    return 0;
}

void
case_string_is_empty()
{
    struct string s1 = {0, NULL};
    struct string s2 = string("s");
    assert(string_is_empty(&s1));
    assert(!string_is_empty(&s2));
}
