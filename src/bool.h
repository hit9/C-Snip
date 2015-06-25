/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifndef _BOOL_H
#define _BOOL_H

#if !defined(__cplusplus)

#if __STDC_VERSION__ >= 199901L
/* C99 */
#include <stdbool.h>

#else

typedef enum {
    false = 0,
    true = 1,
} bool_t;

typedef bool_t bool;

#endif

#endif

#endif
