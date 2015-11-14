/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

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
        table[sub[idx]] = last - idx;

    /* do search */
    size_t i, j, k, t, skip;

    for (i = start; i < s_len; i += skip) {
        skip = 0;
        for (j = 0; j < len; j++) {
            k = last - j;
            if (sub[k] != s[i + k]) {
                t = table[s[i + k]];
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
