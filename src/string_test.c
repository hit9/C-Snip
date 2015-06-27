/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <string.h>
#include "test.h"
#include "string.h"

void
case_string_clear()
{
    struct string *s1 = string("test");
    struct string *s2 = string(NULL);
    assert(!string_isempty(s1));
    assert(string_isempty(s2));
    string_clear(s1);
    string_clear(s2);
    assert(string_isempty(s1));
    assert(string_isempty(s2));
    string_free(s1);
    string_free(s2);
}

void
case_string_put()
{
    struct string *s1 = string(NULL);
    struct string *s2 = string("abcdef");
    const char *p = "abc";
    const char *q = "def";
    assert(string_put(s1, (char *)p, strlen(p)) == ERR_OK);
    assert(string_put(s1, (char *)q, strlen(q)) == ERR_OK);
    assert(string_equals(s1, s2));
    string_free(s1);
    string_free(s2);
}

void
case_string_puts()
{
    struct string *s = string("abc");
    assert(string_puts(s, "efg") == ERR_OK);
    assert(strcmp(cstring(s), "abcefg") == 0);
    string_free(s);
}

void
case_string_putc()
{
    struct string *s = string(NULL);
    assert(string_putc(s, 'a') == ERR_OK);
    assert(string_putc(s, 'b') == ERR_OK);
    assert(strcmp(cstring(s), "ab") == 0);
    string_free(s);
}

void
case_string_concat()
{
    struct string *s = string("abc");
    struct string *t = string("efg");
    assert(string_concat(s, t) == ERR_OK);
    assert(strcmp(cstring(s), "abcefg") == 0);
    string_free(s);
    string_free(t);
}

void
case_string_isempty()
{
    struct string *s1 = string(NULL);
    struct string *s2 = string("s");
    struct string *s3 = string("");
    assert(string_isempty(s1));
    assert(!string_isempty(s2));
    assert(string_isempty(s3));
    string_free(s1);
    string_free(s2);
    string_free(s3);
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
case_string_equals()
{
    struct string *s1 = string("abc");
    struct string *s2 = string("abc");
    struct string *s3 = string("abe");
    assert(string_equals(s1, s2));
    assert(!string_equals(s1, s3));
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

void
case_string_index()
{
    struct string *s = string("abcdefg");
    assert(string_index(s, 'a', 0) == 0);
    assert(string_index(s, 'b', 0) == 1);
    assert(string_index(s, 'c', 1) == 2);
    assert(string_index(s, 'g', 3) == 6);
    string_free(s);
}

void
case_string_reverse()
{
    struct string *s = string("abcdefg");
    string_reverse(s);
    assert(strcmp(cstring(s), "gfedcba") == 0);
    string_free(s);
}

void
case_string_sprintf()
{
    struct string *s = string(NULL);
    string_sprintf(s, "%s%s%s", "a", "bc", "d");
    string_sprintf(s, "%s %s %d", "x", "yz", 123);
    assert(strcmp(cstring(s), "abcdx yz 123") == 0);
    string_free(s);
}

void
case_string_search()
{
    struct string *s = string("this is a simple example");
    assert(string_search(s, "this", 0) == 0);
    assert(string_search(s, "is", 0) == 2);
    assert(string_search(s, "is", 3) == 5);
    assert(string_search(s, "mp", 0) == 12);
    assert(string_search(s, "mp", 13) == 20);
    assert(string_search(s, "not exist", 0) == s->len);
    string_free(s);
}
