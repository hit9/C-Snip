/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

/* Search null-terminated string `sub` in string `s`, simple version via
 * Boyer Moore string search algorithm. Return the first position of the
 * `sub` in the `s`, return the `s`'s length on failure. */
size_t
strings_search(char *s, char *sub, size_t start)
{
    assert(s != NULL && sub != NULL);

    size_t s_len = strlen(s);
    size_t len = strlen(sub);
    size_t last = len - 1;
    size_t idx;

    size_t table[256] = {0};

    /* build bad char table */
    for (idx = 0; idx < 256; idx++)
        table[idx] = len;

    for (idx = 0; idx < len; idx++)
        table[(int)sub[idx]] = last - idx;

    /* do search */
    size_t i, j, k, t, skip;

    for (i = start; i < s_len; i += skip) {
        skip = 0;
        for (j = 0; j < len; j++) {
            k = last - j;
            if (sub[k] != s[i + k]) {
                t = table[(int)s[i + k]];
                skip = t > j? t - j : 1;
                break;
            }
        }
        if (skip == 0)
            // hit
            return i;
    }
    // failed
    return s_len;
}

/* Create random string with length `len`, you may want
 * to set rand seed before all your `rand` calls. */
char *
strings_rand(char *s, size_t len)
{
    static const char chs[] = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int mask = 10 + 26 * 2 - 1;

    int i;

    for (i = 0; i < len; i++)
        s[i] = chs[rand() & mask];

    s[len] = 0;
    return s;
}

/* Replace all `sub` in string `src` with `rep` and concat the
 * result into `dst`. All the arguments are NULL-terminated c
 * string, return  */
char *
strings_replace(char *dst, char *src, char *sub, char *rep)
{
    size_t src_len = strlen(src);
    size_t sub_len = strlen(sub);
    size_t rep_len = strlen(rep);
    size_t dst_len = 0;
    size_t idx, start = 0;

    while ((idx = strings_search(src, sub, start)) < src_len) {
        strncat(dst + dst_len, src + start, idx - start);
        dst_len += idx - start;
        strcat(dst + dst_len, rep);
        dst_len += rep_len;
        start = idx + sub_len;
    }
    strcat(dst + dst_len, src + start);
    dst_len += src_len - start;
    dst[dst_len] = '\0';
    return dst;
}
