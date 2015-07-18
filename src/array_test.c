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

void
case_array_push()
{
    struct array *array = array(0);
    char *s1 = "a", *s2 = "b", *s3 = "c";
    assert(array_push(array, s1) == ARRAY_OK);
    assert(array_len(array) == 1);
    assert(array_push(array, s2) == ARRAY_OK);
    assert(array_len(array) == 2);
    assert(array_push(array, s3) == ARRAY_OK);
    assert(array_len(array) == 3);
    assert(array_get(array, 0) == s1);
    assert(array_get(array, 1) == s2);
    assert(array_get(array, 2) == s3);
    array_free(array);
}

void
case_array_mpush()
{
    struct array *array = array(0);
    char *data[3] = {"s1", "s2", "s3"};
    assert(array_mpush(array, (void **)data, 3) == ARRAY_OK);
    assert(array_len(array) == 3);
    assert(array_get(array, 0) == data[0]);
    assert(array_get(array, 1) == data[1]);
    assert(array_get(array, 2) == data[2]);
    array_free(array);
}

void
case_array_pop()
{
    struct array *array = array(0);
    char *data[3] = {"s1", "s2", "s3"};
    assert(array_mpush(array, (void **)data, 3) == ARRAY_OK);
    assert(array_pop(array, 2) == data[2]);
    assert(array_len(array) == 2);
    assert(array_pop(array, 0) == data[0]);
    assert(array_len(array) == 1);
    assert(array_pop(array, 0) == data[1]);
    assert(array_len(array) == 0);
    array_free(array);
}

void
case_array_index_has()
{
    struct array *array = array(0);
    char *data[3] = {"s1", "s2", "s3"};
    assert(array_mpush(array, (void **)data, 3) == ARRAY_OK);
    assert(array_index(array, "s1", 0) == 0);
    assert(array_index(array, "s2", 1) == 1);
    assert(array_index(array, "s3", 0) >= 2);
    assert(array_index(array, "s2", 2) == array_len(array));
    assert(array_has(array, "s1"));
    assert(array_has(array, "s2"));
    assert(!array_has(array, "s4"));
    array_free(array);
}

void
case_array_extend()
{
    struct array *a = array(0), *b = array(0);
    char *data[3] = {"s1", "s2", "s3"};
    array_mpush(a, (void **)data, 3);
    array_mpush(b, (void **)data, 3);
    assert(array_extend(a, b) == ARRAY_OK);
    assert(array_len(a) == 6);
    assert(array_get(a, 3) == data[0]);
    assert(array_get(a, 4) == data[1]);
    assert(array_get(a, 5) == data[2]);
    array_free(a);
    array_free(b);
}
