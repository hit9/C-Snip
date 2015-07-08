/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "test.h"
#include "errors.h"
#include "list.h"

void
case_list_clear()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, s1) == ERR_OK);
    assert(list_lpush(list, s2) == ERR_OK);
    assert(list_lpush(list, s3) == ERR_OK);
    assert(list->size == 3);
    list_clear(list);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    list_free(list);
}

void
case_list_lpush()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, s1) == ERR_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s1);
    assert(list->size == 1);
    assert(list_lpush(list, s2) == ERR_OK);
    assert(list->head->data == s2);
    assert(list->tail->data == s1);
    assert(list->size == 2);
    assert(list_lpush(list, s3) == ERR_OK);
    assert(list->head->data == s3);
    assert(list->tail->data == s1);
    assert(list->size == 3);
    list_free(list);
}

void
case_list_rpush()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, s1) == ERR_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s1);
    assert(list->size == 1);
    assert(list_rpush(list, s2) == ERR_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s2);
    assert(list->size == 2);
    assert(list_rpush(list, s3) == ERR_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s3);
    assert(list->size == 3);
    list_free(list);
}
