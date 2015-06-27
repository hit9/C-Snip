/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic string implementation.
 */

#ifndef _CW_STRING_H
#define _CW_STRING_H    1

#include <stdint.h>
#include "errors.h"
#include "bool.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define STRING_MAX_CAPACITY_SIZE  16*1024*1024   /* max string capacity: 16mb */
#define STRING_MIN_REALLOC_UNIT   1              /* min string realloc unit: 1mb */
#define STRING_MAX_REALLOC_UNIT   1024*1024      /* max string realloc unit: 1mb */

#define string(cs)                string_new(cs)
#define cstring(s)                string_cstring(s)

struct string {
    size_t  len;    /* string length */
    size_t  cap;    /* string capacity */
    char    *buf;   /* string dynamic buffer */
};

struct string *string_new(const char *cs);
struct string *string_empty(void);
char *string_cstring(struct string *s);
void string_free(struct string *s);
void string_clear(struct string *s);
void string_reverse(struct string *s);
error_t string_grow(struct string *s, size_t size);
error_t string_put(struct string *s, char *buf, size_t len);
error_t string_puts(struct string *s, const char *cs);
error_t string_putc(struct string *s, char ch);
error_t string_concat(struct string *s, struct string *t);
bool string_isempty(struct string *s);
bool string_isspace(struct string *s);
bool string_startswith(struct string *s, struct string *prefix);
bool string_endswith(struct string *s, struct string *suffix);
bool string_equals(struct string *s1, struct string *s2);
int string_cmp(struct string *s1, struct string *s2);
int string_ncmp(struct string *s1, struct string *s2, size_t n);
size_t string_index(struct string *s, char ch, size_t start);

#if defined(__cplusplus)
}
#endif

#endif
