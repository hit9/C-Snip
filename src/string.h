/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifndef _STRING_H
#define _STRING_H

#include <stdint.h>
#include "bool.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct string {
    uint32_t len;   /* string length */
    uint8_t *data;  /* string data */
};

#define string_null  { 0, NULL }
#define string(cstring)  { sizeof(cstring) - 1, (uint8_t *)(cstring) }

bool string_is_empty(struct string *);

#if defined(__cplusplus)
}
#endif

#endif
