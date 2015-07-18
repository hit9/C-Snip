/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic array implementation.
 */

#ifndef _CW_ARRAY_H
#define _CW_ARRAY_H    1

#include <stdint.h>
#include <stdio.h>
#include "bool.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* note that real allocated size is cap * sizeof(void *). */
#define ARRAY_CAP_MAX    16*1024*1024  /* max array capacity: 16mb */
#define ARRAY_UNIT_MIN   1             /* min array realloc unit: 1 */
#define ARRAY_UNIT_MAX   1024*1024     /* max array realloc unit: 1mb */

#define array(cap)      array_new(cap)

enum {
    ARRAY_OK = 0,             /* operation is ok */
    ARRAY_ENOMEM = 1,         /* no memory error */
};

struct array {
    size_t len;               /* array length */
    size_t cap;               /* array capacity */
    void **data;              /* array data */
};

struct array *array_new(size_t cap);
struct array *array_empty(void);
void array_clear(struct array *array);
void array_free(struct array *array);
size_t array_len(struct array *array);
bool array_isempty(struct array *array);
int array_grow(struct array *array, size_t cap);
int array_insert(struct array *array, void *data, size_t idx);
int array_push(struct array *array, void *data);
int array_mpush(struct array *array, void **data, size_t len);
void *array_pop(struct array *array, size_t idx);
void *array_get(struct array *array, size_t idx);
size_t array_index(struct array *array, void *data, size_t start);
int array_extend(struct array *a, struct array *b);

#if defined(__cplusplus)
}
#endif

#endif
