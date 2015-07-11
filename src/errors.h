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
    ERR_FAILED = 2,
} error_t;

/* static const char *errors[] = { */
/*     "Operation is OK", */
/*     "No memory or data is too large", */
/*     "Operation failed", */
/* }; */

#if defined(__cplusplus)
}
#endif

#endif
