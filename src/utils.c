/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>
#include <stdlib.h>
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

/**
 * ****************  Date Time Utils **********************
 */

/* Get time now in ms */
double
time_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000.0;
}
