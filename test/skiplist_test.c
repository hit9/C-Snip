/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "skiplist.h"

void
case_skiplist_base()
{
    struct skiplist *skiplist = skiplist(NULL);
    assert(skiplist != NULL);
    assert(skiplist->len == 0);
    assert(skiplist->head != NULL);
    assert(skiplist->tail == skiplist->head);
    assert(skiplist->level == 1);
    assert(skiplist_push(skiplist, 2, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 1, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 3, NULL) == SKIPLIST_OK);
    assert(skiplist_len(skiplist) == 3);
    assert(skiplist_level(skiplist) <= SKIPLIST_LEVEL_MAX);
    assert(skiplist->tail->score == 3);
    skiplist_clear(skiplist);
    assert(skiplist_level(skiplist) == 1);
    assert(skiplist_len(skiplist) == 0);
    assert(skiplist->head != NULL);
    assert(skiplist->tail == skiplist->head);
    skiplist_free(skiplist);
}

void
case_skiplist_push()
{
    struct skiplist *skiplist = skiplist(NULL);
    struct skiplist_iter *iter = skiplist_iter(skiplist);
    assert(skiplist != NULL && iter != NULL);
    assert(skiplist_push(skiplist, 3, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 9, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 7, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 2, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 6, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 5, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 8, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 1, NULL) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 4, NULL) == SKIPLIST_OK);
    assert(skiplist_len(skiplist) == 9);
    assert(skiplist_level(skiplist) > 0);
    assert(skiplist_iter_next(iter)->score == 1);
    assert(skiplist_iter_next(iter)->score == 2);
    assert(skiplist_iter_next(iter)->score == 3);
    assert(skiplist_iter_next(iter)->score == 4);
    assert(skiplist_iter_next(iter)->score == 5);
    assert(skiplist_iter_next(iter)->score == 6);
    assert(skiplist_iter_next(iter)->score == 7);
    assert(skiplist_iter_next(iter)->score == 8);
    assert(skiplist_iter_next(iter)->score == 9);
    assert(skiplist_first(skiplist)->score == 1);
    assert(skiplist_last(skiplist)->score == 9);
    skiplist_iter_rewind(iter);
    struct skiplist_node *first = skiplist_iter_next(iter);
    struct skiplist_node *second = skiplist_iter_next(iter);
    struct skiplist_node *last = skiplist_last(skiplist);
    assert(skiplist->head->forwards[0] == first);
    assert(first != skiplist->head);
    assert(first->forwards[0] == second);
    assert(second->backward == first);
    assert(first->backward == skiplist->head);
    assert(last->backward != NULL);
    assert(last->forwards[0] == NULL);
    skiplist_iter_free(iter);
    skiplist_free(skiplist);
}

void
case_skiplist_pop()
{
    struct skiplist *skiplist = skiplist(NULL);
    struct skiplist_iter *iter = skiplist_iter(skiplist);
    assert(skiplist != NULL && iter != NULL);
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7,
        v8 = 8, v9 = 9;
    assert(skiplist_push(skiplist, 3, (void *)(&v3)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 9, (void *)(&v9)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 7, (void *)(&v7)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 2, (void *)(&v2)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 6, (void *)(&v6)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 5, (void *)(&v5)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 8, (void *)(&v8)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 1, (void *)(&v1)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 4, (void *)(&v4)) == SKIPLIST_OK);
    assert(skiplist_len(skiplist) == 9);
    assert(skiplist_level(skiplist) > 0);
    assert(skiplist_last(skiplist)->score == 9);
    assert(skiplist_pop(skiplist, 3) == &v3);
    assert(skiplist_pop(skiplist, 4) == &v4);
    assert(skiplist_pop(skiplist, 9) == &v9);
    assert(skiplist_pop(skiplist, 1) == &v1);
    assert(skiplist_len(skiplist) == 5);
    assert(skiplist_first(skiplist)->score == 2);
    assert(skiplist->head->forwards[skiplist->level-1] != NULL);
    skiplist_iter_free(iter);
    skiplist_free(skiplist);
}

void
case_skiplist_popfirst()
{
    struct skiplist *skiplist = skiplist(NULL);
    struct skiplist_iter *iter = skiplist_iter(skiplist);
    assert(skiplist != NULL && iter != NULL);
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7,
        v8 = 8, v9 = 9;
    assert(skiplist_push(skiplist, 3, (void *)(&v3)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 9, (void *)(&v9)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 7, (void *)(&v7)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 2, (void *)(&v2)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 6, (void *)(&v6)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 5, (void *)(&v5)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 8, (void *)(&v8)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 1, (void *)(&v1)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 4, (void *)(&v4)) == SKIPLIST_OK);
    assert(skiplist_len(skiplist) == 9);
    assert(skiplist_level(skiplist) > 0);
    assert(skiplist_popfirst(skiplist) == &v1);
    assert(skiplist_popfirst(skiplist) == &v2);
    assert(skiplist_popfirst(skiplist) == &v3);
    assert(skiplist_popfirst(skiplist) == &v4);
    assert(skiplist_len(skiplist) == 5);
    assert(skiplist_level(skiplist) > 0);
    assert(skiplist->head->forwards[skiplist->level-1] != NULL);
    struct skiplist_node *first = skiplist_iter_next(iter);
    struct skiplist_node *second = skiplist_iter_next(iter);
    assert(first->score == 5);
    assert(second->score == 6);
    assert(first->backward == skiplist->head);
    assert(first->forwards[0] == second);
    assert(second->backward == first);
    assert(skiplist->tail != first && skiplist->tail != second);
    assert(skiplist_popfirst(skiplist) == &v5);
    assert(skiplist_popfirst(skiplist) == &v6);
    assert(skiplist_popfirst(skiplist) == &v7);
    assert(skiplist_popfirst(skiplist) == &v8);
    assert(skiplist_last(skiplist)->score == 9);
    assert(skiplist_popfirst(skiplist) == &v9);
    assert(skiplist_last(skiplist) == NULL);
    assert(skiplist_level(skiplist) == 1);
    assert(skiplist_len(skiplist) == 0);
    skiplist_iter_free(iter);
    skiplist_free(skiplist);
}

void
case_skiplist_poplast()
{
    struct skiplist *skiplist = skiplist(NULL);
    struct skiplist_iter *iter = skiplist_iter(skiplist);
    assert(skiplist != NULL && iter != NULL);
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7,
        v8 = 8, v9 = 9;
    assert(skiplist_push(skiplist, 3, (void *)(&v3)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 9, (void *)(&v9)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 7, (void *)(&v7)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 2, (void *)(&v2)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 6, (void *)(&v6)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 5, (void *)(&v5)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 8, (void *)(&v8)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 1, (void *)(&v1)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 4, (void *)(&v4)) == SKIPLIST_OK);
    assert(skiplist_len(skiplist) == 9);
    assert(skiplist_level(skiplist) > 0);
    assert(skiplist_poplast(skiplist) == &v9);
    assert(skiplist_poplast(skiplist) == &v8);
    assert(skiplist_poplast(skiplist) == &v7);
    assert(skiplist_poplast(skiplist) == &v6);
    assert(skiplist_poplast(skiplist) == &v5);
    assert(skiplist_last(skiplist)->score == 4);
    assert(skiplist_first(skiplist)->score == 1);
    assert(skiplist->tail->score == 4);
    assert(skiplist->tail->backward->score == 3);
    assert(skiplist->tail->backward->backward->score == 2);
    assert(skiplist->head->forwards[skiplist->level-1] != NULL);
    skiplist_iter_free(iter);
    skiplist_free(skiplist);
}

void
case_skiplist_get()
{
    struct skiplist *skiplist = skiplist(NULL);
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7,
        v8 = 8, v9 = 9;
    assert(skiplist_push(skiplist, 3, (void *)(&v3)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 9, (void *)(&v9)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 7, (void *)(&v7)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 2, (void *)(&v2)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 6, (void *)(&v6)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 5, (void *)(&v5)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 8, (void *)(&v8)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 1, (void *)(&v1)) == SKIPLIST_OK);
    assert(skiplist_push(skiplist, 4, (void *)(&v4)) == SKIPLIST_OK);
    assert(skiplist_len(skiplist) == 9);
    assert(skiplist_get(skiplist, 8) == &v8);
    assert(skiplist_get(skiplist, 9) == &v9);
    assert(skiplist_get(skiplist, 1) == &v1);
    assert(skiplist_get(skiplist, 2) == &v2);
    assert(skiplist_get(skiplist, 10) == NULL);
    assert(skiplist_get(skiplist, 9999) == NULL);
    skiplist_free(skiplist);
}
