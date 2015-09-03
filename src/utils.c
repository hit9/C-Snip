/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdlib.h>
#include <sys/time.h>

/* Get time now in ms */
double
time_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000.0;
}
