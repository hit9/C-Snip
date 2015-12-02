/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "list.h"

void
case_list_clear()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, s1) == LIST_OK);
    assert(list_lpush(list, s2) == LIST_OK);
    assert(list_lpush(list, s3) == LIST_OK);
    assert(list_len(list) == 3);
    list_clear(list);
    assert(list_len(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    list_free(list);
}

void
case_list_lpush()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, s1) == LIST_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s1);
    assert(list_len(list) == 1);
    assert(list_lpush(list, s2) == LIST_OK);
    assert(list->head->data == s2);
    assert(list->tail->data == s1);
    assert(list_len(list) == 2);
    assert(list_lpush(list, s3) == LIST_OK);
    assert(list->head->data == s3);
    assert(list->tail->data == s1);
    assert(list_len(list) == 3);
    list_free(list);
}

void
case_list_rpush()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, s1) == LIST_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s1);
    assert(list_len(list) == 1);
    assert(list_rpush(list, s2) == LIST_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s2);
    assert(list_len(list) == 2);
    assert(list_rpush(list, s3) == LIST_OK);
    assert(list->head->data == s1);
    assert(list->tail->data == s3);
    assert(list_len(list) == 3);
    list_free(list);
}

void
case_list_lpop()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, s1) == LIST_OK);
    assert(list_rpush(list, s2) == LIST_OK);
    assert(list_rpush(list, s3) == LIST_OK);
    assert(list_len(list) == 3);
    assert(list->head->data == s1);
    assert(list_lpop(list) == s1);
    assert(list_len(list) == 2);
    assert(list->head->data == s2);
    assert(list_lpop(list) == s2);
    assert(list_len(list) == 1);
    assert(list->head->data == s3);
    assert(list_lpop(list) == s3);
    assert(list_len(list) == 0);
    assert(list->head == NULL);
    list_free(list);
}

void
case_list_rpop()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, s1) == LIST_OK);
    assert(list_lpush(list, s2) == LIST_OK);
    assert(list_lpush(list, s3) == LIST_OK);
    assert(list_len(list) == 3);
    assert(list->tail->data == s1);
    assert(list_rpop(list) == s1);
    assert(list_len(list) == 2);
    assert(list->tail->data == s2);
    assert(list_rpop(list) == s2);
    assert(list_len(list) == 1);
    assert(list->tail->data == s3);
    assert(list_rpop(list) == s3);
    assert(list_len(list) == 0);
    assert(list->tail == NULL);
    list_free(list);
}

void
case_list_iter()
{
    struct list *list = list();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    list_push(list, s1);
    list_push(list, s2);
    list_push(list, s3);
    struct list_iter *iter = list_iter(list);
    assert(iter->list == list);
    assert(iter->node == list->head);
    assert(list_iter_next(iter) == s1);
    assert(list_iter_next(iter) == s2);
    assert(list_iter_next(iter) == s3);
    list_iter_seek_tail(iter);
    assert(list_iter_prev(iter) == s3);
    assert(list_iter_prev(iter) == s2);
    assert(list_iter_prev(iter) == s1);
    list_iter_free(iter);
    int i = 0;
    list_each(list, {
        char *s = data;
        assert(s[1] - 49 == i);
        i += 1;
    });
    assert(list_len(list) == i);
    list_free(list);
}
