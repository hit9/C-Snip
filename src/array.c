/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "array.h"

/* Create array and init cap. */
struct array *
array_new(size_t cap)
{
    struct array *array = malloc(sizeof(struct array));

    if (array != NULL) {
        array->len = 0;
        array->cap = 0;
        array->data = NULL;

        if (cap > 0 && array_grow(array, cap) != ARRAY_OK)
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

/* Test if array is empty. */
bool
array_isempty(struct array *array)
{
    assert(array != NULL);

    if (array->len == 0)
        return true;
    return false;
}


/* Grow array capacity to given cap. */
int
array_grow(struct array *array, size_t cap)
{
    assert(array != NULL);

    if (cap > ARRAY_CAP_MAX)
        return ARRAY_ENOMEM;

    if (cap <= array->cap)
        return ARRAY_OK;

    size_t unit = array->cap;

    if (unit > ARRAY_UNIT_MAX)
        unit = ARRAY_UNIT_MAX;

    if (unit < ARRAY_UNIT_MIN)
        unit = ARRAY_UNIT_MIN;

    size_t new_cap = array->cap + unit;
    while (new_cap < cap)
        new_cap += unit;

    void **data = realloc(array->data,
            new_cap * sizeof(void *));

    if (data == NULL)
        return ARRAY_ENOMEM;

    array->data = data;
    array->cap = new_cap;
    return ARRAY_OK;
}

/* Get array length. */
size_t
array_len(struct array *array)
{
    assert(array != NULL);
    return array->len;
}

/* Insert an item at postion `idx`. */
int
array_insert(struct array *array, void *data, size_t idx)
{
    assert(array != NULL);

    int error = array_grow(array, array->len + 1);

    if (error != ARRAY_OK)
        return error;

    assert(idx <= array->len);

    size_t i = array->len;

    while (i > idx) {
        array->data[i] = array->data[i-1];
        i -= 1;
    }

    array->data[idx] = data;
    array->len += 1;
    return ARRAY_OK;
}

/* Push an item on right. */
int
array_push(struct array *array, void *data)
{
    int error = array_grow(array, array->len + 1);

    if (error == ARRAY_OK) {
        array->data[array->len] = data;
        array->len += 1;
    }
    return error;
}

/* Pop an item at position `idx`, NULL on empty. */
void *
array_pop(struct array *array, size_t idx)
{
    assert(array != NULL);

    if (array->len == 0)
        return NULL;

    assert(array->data != NULL && idx < array->len);

    void *data = array->data[idx];

    while (idx < array->len - 1) {
        array->data[idx] = array->data[idx+1];
        idx += 1;
    }

    array->len -= 1;
    return data;
}

/* Get an item by `idx`. */
void *
array_get(struct array *array, size_t idx)
{
    assert(array != NULL && array->data != NULL &&
            array->len > idx);
    return array->data[idx];
}

/* Push multiple items to array. */
int
array_mpush(struct array *array, void **data, size_t len)
{
    assert(array != NULL);

    int error = array_grow(array, array->len + len);

    if (error == ARRAY_OK) {
        size_t idx;

        for (idx = 0; idx < len; idx++)
            array->data[array->len + idx] = data[idx];

        array->len += len;
    }
    return error;
}

/* Find item index in array. */
size_t
array_index(struct array *array, void *data, size_t start)
{
    assert(array != NULL);

    size_t idx;

    for (idx = start; idx < array->len
            && array->data[idx] != data; idx++);

    if (idx < array->len)
        return idx;     /* got */
    return array->len;  /* not found */
}

/* If an item is in array. */
bool
array_has(struct array *array, void *data)
{
    assert(array != NULL);

    if (array_index(array, data, 0) < array->len)
        return true;
    return false;
}
