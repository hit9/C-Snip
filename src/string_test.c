/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "test.h"
#include "string.h"

void
case_string_isempty()
{
    struct string *s1 = string(NULL);
    struct string *s2 = string("s");
    assert(string_isempty(s1));
    assert(!string_isempty(s2));
    string_free(s1);
    string_free(s2);
}

void
case_string_isspace()
{
    struct string *s1 = string(NULL);
    struct string *s2 = string(" \t\n");
    struct string *s3 = string("abc");
    assert(!string_isspace(s1));
    assert(string_isspace(s2));
    assert(!string_isspace(s3));
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

void
case_string_startswith()
{
    struct string *s1 = string("abc");
    struct string *s2 = string("ab");
    struct string *s3 = string("ac");
    assert(string_startswith(s1, s2));
    assert(!string_startswith(s1, s3));
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

void
case_string_endswith()
{
    struct string *s1 = string("abcd");
    struct string *s2 = string("bcd");
    struct string *s3 = string("ecd");
    struct string *s4 = string("d");
    assert(string_endswith(s1, s2));
    assert(!string_endswith(s1, s3));
    assert(!string_endswith(s2, s3));
    assert(string_endswith(s1, s4));
    assert(string_endswith(s2, s4));
    assert(string_endswith(s3, s4));
    assert(string_endswith(s4, s4));
    string_free(s1);
    string_free(s2);
    string_free(s3);
    string_free(s4);
}

void
case_string_ncmp()
{
    struct string *s1 = string("abc");
    struct string *s2 = string("abc");
    struct string *s3 = string("abd");
    assert(string_ncmp(s1, s2, 3) == 0);
    assert(string_ncmp(s1, s2, 2) == 0);
    assert(string_ncmp(s1, s3, 2) == 0);
    assert(string_ncmp(s1, s3, 3) < 0);
    assert(string_ncmp(s3, s1, 3) > 0);
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

void
case_string_cmp()
{
    struct string *s1 = string("abc");
    struct string *s2 = string("abcd");
    struct string *s3 = string("abc");
    assert(string_cmp(s1, s2) < 0);
    assert(string_cmp(s2, s1) > 0);
    assert(string_cmp(s1, s3) == 0);
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

void
case_string_index()
{
    struct string *s = string("abcdefg");
    assert(string_index(s, (uint8_t)'a', 0) == 0);
    assert(string_index(s, (uint8_t)'b', 0) == 1);
    assert(string_index(s, (uint8_t)'c', 1) == 2);
    assert(string_index(s, (uint8_t)'g', 3) == 6);
    string_free(s);
}
