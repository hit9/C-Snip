/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <sys/time.h>
#include <time.h>

/* Get timestamp (in milliseconds) for now. */
double datetime_stamp_now(void) {
#if defined CLOCK_REALTIME
    struct timespec ts;
    int rc = clock_gettime(CLOCK_REALTIME, &ts);
    assert(rc == 0);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000.0;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000.0;
#endif
}
