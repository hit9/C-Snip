/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifndef _CW_BOOL_H
#define _CW_BOOL_H  1

#if !defined(__cplusplus)

#if __STDC_VERSION__ >= 199901L
/* C99 */
#include <stdbool.h>

#else

typedef enum {
    false   = 0,
    true    = 1,
} bool;

#endif

#endif

#endif
