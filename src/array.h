/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic array implementation.
 */


#ifndef _CW_ARRAY_H
#define _CW_ARRAY_H    1

#include <stdint.h>
#include "errors.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct array {
    size_t size;
    size_t cap;
    void **data;
};

struct array *array_new(size_t size);
struct array *array_empty(void);
void array_clear(struct array *array);
void array_free(struct array *array);
error_t array_grow(struct array *array, size_t size);
error_t array_push(struct array *array, void *data);
void *array_shift(struct array *array);
void *array_pop(struct array *array);
size_t array_index(struct array *array, void *data, size_t start);
error_t array_extend(struct array *a, struct array *b);

#if defined(__cplusplus)
}
#endif

#endif
