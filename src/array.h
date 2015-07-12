/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic array implementation.
 */

#ifndef _CW_ARRAY_H
#define _CW_ARRAY_H    1

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define ARRAY_MAX_CAPACITY_SIZE  16*1024*1024   /* max array capacity: 16mb */
#define ARRAY_MIN_REALLOC_UNIT   1              /* min array realloc unit: 1 */
#define ARRAY_MAX_REALLOC_UNIT   1024*1024      /* max array realloc unit: 1mb */

#define array(size)                    array_new(size)
#define array_insert(arr, idx, data)   array_unshift(arr, idx, data)

enum {
    ARRAY_OK = 0,             /* operation is ok */
    ARRAY_ENOMEM = 1,         /* no memory error */
};

struct array {
    size_t size;              /* array size */
    size_t cap;               /* array capacity */
    void **data;              /* array data */
};

struct array *array_new(size_t size);
struct array *array_empty(void);
void array_clear(struct array *array);
void array_free(struct array *array);
int array_grow(struct array *array, size_t size);
int array_push(struct array *array, void *data);
void *array_pop(struct array *array);
void *array_shift(struct array *array);
void *array_unshift(struct array *array, size_t idx, void *data);
size_t array_index(struct array *array, void *data, size_t start);
int array_extend(struct array *a, struct array *b);

#if defined(__cplusplus)
}
#endif

#endif
