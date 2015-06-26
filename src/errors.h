/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifndef _CW_ERRORS_H
#define _CW_ERRORS_H    1

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
    ERR_OK = 0,
    ERR_NOMEM = 1,
} error_t;

#if defined(__cplusplus)
}
#endif

#endif
