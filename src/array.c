/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "array.h"

/* Create array and init size. */
struct array *
array_new(size_t size)
{
    struct array *array = malloc(sizeof(struct array));

    if (array != NULL) {
        array->size = 0;
        array->cap = 0;
        array->data = NULL;

        if (size > 0 && array_grow(array, size) != ERR_OK)
            return NULL;
    }
    return array;
}

/* Create empty array. */
struct array *
array_empty(void)
{
    return array_new(0);
}

/* Free array. */
void
array_free(struct array *array)
{
    if (array != NULL) {
        if (array->data != NULL)
            free(array->data);
        free(array);
    }
}

/* Grow array capacity to given size. */
int
array_grow(struct array *array, size_t size)
{
    assert(array != NULL);

    if (size > ARRAY_MAX_CAPACITY_SIZE)
        return ARRAY_ENOMEM;

    if (size <= array->cap)
        return ARRAY_OK;

    size_t cap = array->cap;
    size_t unit = array->cap;

    if (unit > ARRAY_MAX_REALLOC_UNIT)
        unit = ARRAY_MAX_REALLOC_UNIT;

    if (unit < ARRAY_MIN_REALLOC_UNIT)
        unit = ARRAY_MIN_REALLOC_UNIT;

    while (cap < size)
        cap += unit;

    char *buf = realloc(array->buf, cap);

    if (buf == NULL)
        return STRING_ENOMEM;

    array->buf = buf;
    array->cap = cap;
    return ARRAY_OK;
}
