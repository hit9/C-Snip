/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>
#include "test.h"
#include "array.h"

void
case_array_empty()
{
    struct array *array = array_empty();
    assert(array_isempty(array));
    array_free(array);
}

void
case_array_insert()
{
    struct array *array = array(0);
    char *s1 = "a", *s2 = "b", *s3 = "c";
    assert(array_insert(array, s1, 0) == ARRAY_OK);
    assert(array_len(array) == 1);
    assert(array_get(array, 0) == s1);
    assert(array_insert(array, s2, 0) == ARRAY_OK);
    assert(array_insert(array, s3, 0) == ARRAY_OK);
    assert(array_len(array) == 3);
    assert(array_get(array, 0) == s3);
    assert(array_get(array, 1) == s2);
    assert(array_get(array, 2) == s1);
    array_free(array);
}
