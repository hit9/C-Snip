/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "string.h"

/* Create a new string and init it with a C null-terminated
 * string if the char array is not NULL. */
struct string *
string_new(const char *cs)
{
    struct string *s = malloc(sizeof(struct string));

    if (s != NULL) {
        s->len = 0;
        s->cap = 0;
        s->buf = NULL;

        if (cs != NULL) {
            if (string_puts(s, cs) != ERR_OK)
                return NULL;
        }
    }

    return s;
}

/* Create a empty string. */
struct string *
string_empty(void)
{
    return string_new(NULL);
}

/* Free a string and its content, no operation is performed
 * if the string is NULL. */
void
string_free(struct string *s)
{
    if (s != NULL) {
        if (s->buf != NULL)
            free(s->buf);
        free(s);
    }
}

/* Clear a string into an empty string. And the content memory
 * will be freed. */
void
string_clear(struct string *s)
{
    assert(s != NULL);

    if (s->buf != NULL)
        free(s->buf);
    s->buf = NULL;
    s->len = 0;
    s->cap = 0;
}

/* Reverse a string in place. */
void
string_reverse(struct string *s)
{
    assert(s != NULL);

    if (s->len == 0)
        return;

    char tmp;
    size_t idx = 0;
    size_t end = s->len - 1;

    while (idx < end) {
        // swap
        tmp = s->buf[idx];
        s->buf[idx] = s->buf[end];
        s->buf[end] = tmp;
        // move
        idx ++;
        end --;
    }
}

/**
 * Return a null-terminated c string.
 */
char *
string_cstring(struct string *s)
{
    assert(s != NULL);

    if (s->len < s->cap && s->buf[s->len] == '\0')
        return s->buf;

    if (s->len + 1 <= s->cap ||
            string_grow(s, s->len + 1) == ERR_OK) {
        s->buf[s->len] = '\0';
        return s->buf;
    }

    return NULL;
}

/* Grow a string's buffer capacity to given size, the new
 * capacity is calculated like k*unit>=size, by default, the
 * unit size is current cap, if the unit is large enough, use
 * STRING_MAX_REALLOC_UNIT instead. */
error_t
string_grow(struct string *s, size_t size)
{
    assert(s != NULL);

    if (size > STRING_MAX_CAPACITY_SIZE)
        return ERR_NOMEM;

    if (size <= s->cap)
        return ERR_OK;

    size_t cap = s->cap;
    size_t unit = s->cap;

    if (unit > STRING_MAX_REALLOC_UNIT)
        unit = STRING_MAX_REALLOC_UNIT;

    if (unit < STRING_MIN_REALLOC_UNIT)
        unit = STRING_MIN_REALLOC_UNIT;

    while (cap < size)
        cap += unit;

    char *buf = realloc(s->buf, cap);

    if (buf == NULL)
        return ERR_NOMEM;

    s->buf = buf;
    s->cap = cap;
    return ERR_OK;
}

/* Put buffer on the end of a string. */
error_t
string_put(struct string *s, char *buf, size_t len)
{
    error_t error = string_grow(s, s->len + len);

    if (error == ERR_OK) {
        memcpy(s->buf + s->len, buf, len);
        s->len += len;
    }

    return error;
}

/* Put null-terminated c string to the end of a string. */
error_t
string_puts(struct string *s, const char *cs)
{
    return string_put(s, (char *)cs, strlen(cs));
}

/* Put single char to the end of a string. */
error_t
string_putc(struct string *s, char ch)
{
    error_t error = string_grow(s, s->len + 1);

    if (error == ERR_OK) {
        s->buf[s->len] = ch;
        s->len += 1;
    }
    return error;
}

/* Concat string on the end of a string. */
error_t
string_concat(struct string *s, struct string *t)
{
    return string_puts(s, cstring(t));
}

/* Truncate string, do nothing if len >= s->len, note that
 * buf will not be freed even if you truncate the string to
 * size 0. */
void
string_truncate(struct string *s, size_t len)
{
    assert(s != NULL);

    if (len < s->len)
        s->len = len;
}

/* Return true if a string is empty. */
bool
string_isempty(struct string *s)
{
    assert(s != NULL);

    if (s->len == 0)
        return true;
    return false;
}

/* Return true if a string is space. */
bool
string_isspace(struct string *s)
{
    assert(s != NULL);

    size_t idx;

    for (idx = 0; idx < s->len; idx++)
        if (!isspace(s->buf[idx]))
            return false;
    if (s->len > 0)
        return true;
    return false;
}

/* Return true if a string starts with prefix. */
bool
string_startswith(struct string *s, struct string *prefix)
{
    assert(s != NULL && prefix != NULL);

    size_t idx = 0;

    while (idx < s->len && idx < prefix->len) {
        if (s->buf[idx] != prefix->buf[idx])
            return false;
        idx++;
    }
    return true;
}

/* Return true if a string ends with suffix. */
bool
string_endswith(struct string *s, struct string *suffix)
{
    assert(s != NULL && suffix != NULL);

    size_t idx = 0;

    while (idx < s->len && idx < suffix->len) {
        if (s->buf[s->len - 1 - idx] !=
                suffix->buf[suffix->len - 1 - idx])
            return false;
        idx++;
    }
    return true;
}

/* Performs like strncmp. */
int
string_ncmp(struct string *s1, struct string *s2, size_t n)
{
    assert(s1 != NULL && s2 != NULL);
    return strncmp(s1->buf, s2->buf, n);
}

/* Performs like strcmp. */
int
string_cmp(struct string *s1, struct string *s2)
{
    assert(s1 != NULL && s2 != NULL);

    if (s1->len > s2->len)
        return 1;

    if (s1->len < s2->len)
        return -1;

    return string_ncmp(s1, s2, s1->len);
}

/* Returns true if two string equals on content. */
bool
string_equals(struct string *s1, struct string *s2)
{
    if (0 == string_cmp(s1, s2))
        return true;
    return false;
}

/* Index a char in a string. */
size_t
string_index(struct string *s, char ch, size_t start)
{
    assert(s != NULL);

    size_t idx;

    for (idx = start; idx < s->len && s->buf[idx] != ch; idx++);

    if (idx < s->len)
        return idx;
    return s->len;
}

void
string_print(struct string *s)
{
    printf("%s", cstring(s));
}

void
string_println(struct string *s)
{
    printf("%s\n", cstring(s));
}

/* Formatted printing to a string. */
error_t
string_sprintf(struct string *s, const char *fmt, ...)
{
    assert(s != NULL);

    if (s->len >= s->cap &&
            string_grow(s, s->len + 1) != ERR_OK)
        return ERR_NOMEM;

    va_list ap;
    int num;

    va_start(ap, fmt);
    num = vsnprintf(s->buf + s->len, s->cap - s->len, fmt, ap);
    va_end(ap);

    if (num < 0)
        return ERR_FAILED;

    size_t size = (size_t)num;

    if (size >= s->cap - s->len) {
        if (string_grow(s, s->len + size + 1) != ERR_OK)
            return ERR_NOMEM;
        va_start(ap, fmt);
        num = vsnprintf(s->buf + s->len,
                s->cap - s->len, fmt, ap);
        va_end(ap);
    }

    if (num < 0)
        return ERR_FAILED;

    s->len += num;
    return ERR_OK;
}

/* Search null-terminated sub-string in a string, return the first
 * position of the sub-string in the string, return the string's
 * length on failure. */
size_t
string_search(struct string *s, char *sub, size_t start)
{
    assert(s != NULL);

    size_t len = strlen(sub);
    size_t last = len - 1;
    size_t idx;

    size_t table[256] = {0};

    // build bad char table
    for (idx = 0; idx < 256; idx++)
        table[idx] = len;
    for (idx = 0; idx < len; idx++)
        table[sub[idx]] = last - idx;

    // search
    size_t i, j, k, t, skip;

    for (i = start; i < s->len; i += skip) {
        skip = 0;
        for (j = 0; j < len; j++) {
            k = last - j;
            if (sub[k] != s->buf[i + k]) {
                t = table[s->buf[i + k]];
                skip = t > j? t - j : 1;
                break;
            }
        }
        if (skip == 0)
            return i;
    }

    return s->len;
}
