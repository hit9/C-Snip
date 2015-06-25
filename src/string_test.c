/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "test.h"
#include "string.h"

void case_string_isempty();
void case_string_ncmp();
void case_string_cmp();
void case_string_isspace();

int
main(int argc, const char *argv[])
{
    struct test_case cases[] = {
        { "string_isempty", &case_string_isempty },
        { "string_isspace", &case_string_isspace },
        { "string_ncmp", &case_string_ncmp },
        { "string_cmp", &case_string_cmp },
        { NULL, NULL },
    };

    run_cases(cases);
    return 0;
}

void
case_string_isempty()
{
    struct string s1 = {0, NULL};
    struct string s2 = string("s");
    assert(string_isempty(&s1));
    assert(!string_isempty(&s2));
}

void
case_string_isspace()
{
    struct string s1 = {0, NULL};
    struct string s2 = string(" \t\n");
    struct string s3 = string("abc");
    assert(!string_isspace(&s1));
    assert(string_isspace(&s2));
    assert(!string_isspace(&s3));
}

void
case_string_ncmp()
{
    struct string s1 = string("abc");
    struct string s2 = string("abc");
    struct string s3 = string("abd");
    assert(string_ncmp(&s1, &s2, 3) == 0);
    assert(string_ncmp(&s1, &s2, 2) == 0);
    assert(string_ncmp(&s1, &s3, 2) == 0);
    assert(string_ncmp(&s1, &s3, 3) < 0);
    assert(string_ncmp(&s3, &s1, 3) > 0);
}

void
case_string_cmp()
{
    struct string s1 = string("abc");
    struct string s2 = string("abcd");
    struct string s3 = string("abc");
    assert(string_cmp(&s1, &s2) < 0);
    assert(string_cmp(&s2, &s1) > 0);
    assert(string_cmp(&s1, &s3) == 0);
}
