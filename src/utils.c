/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "utils.h"

/**
 * **************** Common Utils **********************
 */

int
_scnprintf(char *buf, size_t size, const char *fmt, ...)
{
    va_list args;
    int n;

    va_start(args, fmt);
    n = _vscnprintf(buf, size, fmt, args);
    va_end(args);

    return n;
}

int
_vscnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
    int n;

    n = vsnprintf(buf, size, fmt, args);

    if (n <= 0) {
        return 0;
    }

    if (n < (int) size) {
        return n;
    }

    return (int)(size - 1);
}

/* Search null-terminated string `sub` in string `s`, simple version via
 * Boyer Moore string search algorithm. Return the first position of the
 * `sub` in the `s`, return the `s`'s length on failure. */
size_t
bm_search(char *s, char *sub, size_t start)
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

/* Create random string with length `len`, you may want
 * to set rand seed before all your `rand` calls. */
char *
random_str(char *s, size_t len)
{
    static const char chs[] = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for (i = 0; i < len; i++)
        s[i] = chs[rand() % (10 + 26 * 2)];
    s[len] = 0;
    return s;
}

/**
 * **************** Hash Functions **********************
 */
/* Jenkins Hash function
 * https://en.wikipedia.org/wiki/Jenkins_hash_function */
uint32_t
jenkins_hash(char *key, size_t len)
{
    uint32_t hash, i;

    for(hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

/**
 * **************** Date Time Utils **********************
 */

/* Get time now in ms */
double
time_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000.0;
}
