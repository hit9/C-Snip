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
