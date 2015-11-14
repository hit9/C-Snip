/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <time.h>
#include <sys/time.h>

/* Get timestamp for now. */
long
datetime_stamp_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000;
}
