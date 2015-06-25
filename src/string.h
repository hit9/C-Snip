/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifndef _CW_STRING_H
#define _CW_STRING_H    1

#include <stdint.h>
#include "bool.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define string(cs) string_new(cs)

struct string {
    uint32_t    len;   /* string length */
    uint8_t     *data;  /* string data */
};

struct string *string_new(const char *cs);
bool string_isempty(struct string *s);
bool string_isspace(struct string *s);
bool string_startswith(struct string *s, struct string *prefix);
bool string_endswith(struct string *s, struct string *suffix);
int string_cmp(struct string *s1, struct string *s2);
int string_ncmp(struct string *s1, struct string *s2, uint32_t n);
uint32_t string_index(struct string *s, uint8_t ch, uint32_t start);

#if defined(__cplusplus)
}
#endif

#endif
