/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "skiplist.h"

/* Default score comparator. */
static int
skiplist_default_cmp(unsigned long score1, unsigned long score2)
{
    return score1 - score2;
}

/* Get random level between 1 and level_max. */
static int
skiplist_rand_level(void)
{
    int level = 1;

    while ((rand() & 0xffff) < (SKIPLIST_FACTOR_P * 0xffff))
        level += 1;

    if (level < SKIPLIST_LEVEL_MAX)
        return level;
    return SKIPLIST_LEVEL_MAX;
}

/* Create skiplist node. */
struct skiplist_node *
skiplist_node_new(int level, unsigned long score, void *data)
{
    assert(level > 0);

    struct skiplist_node *node = malloc(sizeof(struct skiplist_node));

    if (node != NULL) {
        node->score = score;
        node->data = data;
        node->backward = NULL;
        node->forwards = malloc(level * sizeof(struct skiplist_node *));

        if (node->forwards == NULL) {
            free(node);
            return NULL;
        }

        int i;
        for (i = 0; i < level; i++)
            node->forwards[i] = NULL;
    }
    return node;
}

/* Free skiplist node. */
void
skiplist_node_free(struct skiplist_node *node)
{
    if (node != NULL) {
        if (node->forwards != NULL)
            free(node->forwards);
        free(node);
    }
}

/* Create skiplist. */
struct skiplist *
skiplist_new(skiplist_cmp_t cmp)
{
    if (cmp == NULL)
        cmp = &skiplist_default_cmp;

    struct skiplist *skiplist = malloc(sizeof(struct skiplist));

    if (skiplist != NULL) {
        skiplist->len = 0;
        skiplist->level = 1;
        skiplist->cmp = cmp;
        skiplist->head = skiplist_node_new(SKIPLIST_LEVEL_MAX, 0, NULL);
        if (skiplist->head == NULL) {
            free(skiplist);
            return NULL;
        }
        skiplist->tail = skiplist->head;
    }
    return skiplist;
}

/* Free skiplist. */
void
skiplist_free(struct skiplist *skiplist)
{
    if (skiplist != NULL) {
        skiplist_clear(skiplist);
        free(skiplist);
    }
}

/* Clear skiplist. */
void
skiplist_clear(struct skiplist *skiplist)
{
    assert(skiplist != NULL);

    while (skiplist_len(skiplist) != 0)
        skiplist_popfirst(skiplist);
}

/* Get skiplist length. */
size_t
skiplist_len(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    return skiplist->len;
}

/* Get skiplist level. */
int skiplist_level(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    return skiplist->level;
}

/* Push data to skiplist. */
int
skiplist_push(struct skiplist *skiplist, unsigned long score, void *data)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);
    assert(skiplist->cmp != NULL);

    struct skiplist_node *update[SKIPLIST_LEVEL_MAX];
    struct skiplist_node *node = skiplist->head;
    int i;

    for (i = skiplist->level - 1; i >= 0; i--) {
        while (node->forwards[i] != NULL &&
                (skiplist->cmp)(node->forwards[i]->score, score) < 0)
            node = node->forwards[i];
        update[i] = node;
    }

    int level = skiplist_rand_level();

    if (level > skiplist->level) {
        for (i = skiplist->level; i < level; i++)
            update[i] = skiplist->head;
        skiplist->level = level;
    }

    node = skiplist_node_new(level, score, data);

    if (node == NULL)
        return SKIPLIST_ENOMEM;

    for (i = 0; i < level; i++) {
        node->forwards[i] = update[i]->forwards[i];
        update[i]->forwards[i] = node;
    }

    node->backward = update[0];

    if (node->forwards[0] == NULL)
        skiplist->tail = node;
    skiplist->len += 1;
    return SKIPLIST_OK;
}

/* Search node by score and return the first target's data, NULL on not found. */
void *
skiplist_search(struct skiplist *skiplist, unsigned long score)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);
    assert(skiplist->cmp != NULL);

    struct skiplist_node *node = skiplist->head;
    int i, result;

    for (i = skiplist->level - 1; i >= 0; i--) {
        while (node->forwards[i] != NULL) {
            result = (skiplist->cmp)(node->forwards[i]->score, score);
            if (result < 0) {
                node = node->forwards[i];
            } else if (result == 0) {
                return node->data;
            } else {
                break;
            }
        }
    }
    /* not found */
    return NULL;
}

/* Pop node by score (the first target), NULL on not found. */
void *skiplist_pop(struct skiplist *skiplist, unsigned long score)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);
    assert(skiplist->cmp != NULL);

    struct skiplist_node *update[SKIPLIST_LEVEL_MAX];
    struct skiplist_node *head = skiplist->head;
    struct skiplist_node *node = head;
    int i;

    for (i = skiplist->level - 1; i >= 0; i--) {
        while (node->forwards[i] != NULL &&
                (skiplist->cmp)(node->forwards[i]->score, score) < 0)
            node = node->forwards[i];
        update[i] = node;
    }

    node = node->forwards[i];

    if (node == NULL)
        /* not found */
        return NULL;

    for (i = 0; i < skiplist->level; i++) {
        if (update[i]->forwards[i] == node)
            update[i]->forwards[i] = node->forwards[i];
    }

    while (skiplist->level > 1 && head->forwards[skiplist->level - 1] == NULL)
        skiplist->level -= 1;

    if (node->forwards[0] != NULL)
        node->forwards[0]->backward = node->backward;

    if (node == skiplist->tail)
        skiplist->tail = node->backward;

    void *data = node->data;
    skiplist_node_free(node);
    skiplist->len -= 1;
    return data;
}

/* Pop the first node and get its data, NULL on empty.
 * We assert that only head can establish forward link
 * to the first node. */
void *
skiplist_popfirst(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);

    if (skiplist->len == 0)
        return NULL;

    struct skiplist_node *head = skiplist->head;
    struct skiplist_node *node = head->forwards[0];
    assert(node != NULL);

    int i;

    for (i = 0; i < skiplist->level; i++) {
        if (head->forwards[i] == node)
            head->forwards[i] = node->forwards[i];
    }

    while (skiplist->level > 1 && head->forwards[skiplist->level - 1] == NULL)
        skiplist->level -= 1;

    if (node->forwards[0] != NULL)
        node->forwards[0]->backward = node->backward;

    if (node == skiplist->tail)
        skiplist->tail = node->backward;

    void *data = node->data;
    skiplist_node_free(node);
    skiplist->len -= 1;
    return data;
}

/* Pop the last node and get its data, NULL on empty.
 * We assert that tail's forwards links
 */
/* FIXME: Any O(1) way ? */
void *
skiplist_poplast(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);

    struct skiplist_node *update[SKIPLIST_LEVEL_MAX];
    struct skiplist_node *head = skiplist->head;
    struct skiplist_node *tail = skiplist->tail;
    struct skiplist_node *node = head;

    int i;

    for (i = skiplist->level - 1; i >= 0; i--) {
        while (node->forwards[i] != NULL && node->forwards[i] != tail)
            node = node->forwards[i];
        update[i] = node;
    }

    for (i = 0; i < skiplist->level; i++) {
        if (update[i]->forwards[i] == tail)
            update[i]->forwards[i] = NULL;
    }

    while (skiplist->level > 1 && head->forwards[skiplist->level - 1] == NULL)
        skiplist->level -= 1;

    void *data = tail->data;
    skiplist->tail = tail->backward;
    skiplist_node_free(tail);
    skiplist->len -= 1;
    return data;
}

/* Get first node, NULL on empty. */
struct skiplist_node *
skiplist_first(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);

    if (skiplist->len == 0)
        return NULL;
    return skiplist->head->forwards[0];
}

/* Get last node, NULL on empty. */
struct skiplist_node *
skiplist_last(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);

    if (skiplist->len == 0)
        return NULL;
    assert(skiplist->tail != skiplist->head);
    return skiplist->tail;
}

/* Create a skiplist iterator. */
struct skiplist_iter *
skiplist_iter_new(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);
    struct skiplist_iter *iter = malloc(sizeof(struct skiplist_iter));

    if (iter != NULL) {
        iter->skiplist = skiplist;
        iter->node = skiplist->head;
    }
    return iter;
}

/* Free skiplist iter. */
void
skiplist_iter_free(struct skiplist_iter *iter)
{
    if (iter != NULL)
        free(iter);
}

/* Seek skiplist next, NULL on end. */
struct skiplist_node *
skiplist_iter_next(struct skiplist_iter *iter)
{
    assert(iter != NULL);
    assert(iter->node != NULL);
    iter->node = iter->node->forwards[0];
    return iter->node;
}

/* Seek skiplist prev, NULL on end. */
struct skiplist_node *
skiplist_iter_prev(struct skiplist_iter *iter)
{
    assert(iter != NULL);
    assert(iter->node != NULL);
    assert(iter->skiplist != NULL);
    iter->node = iter->node->backward;
    if (iter->node == iter->skiplist->head)
        return NULL;
    return iter->node;
}

/* Print the skiplist schema. */
void
skiplist_print(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    assert(skiplist->head != NULL);

    int i;
    struct skiplist_node *node;

    for (i = 0; i < skiplist->level; i++) {
        node = skiplist->head->forwards[i];
        printf("Level[%d]: ", i);
        while (node != NULL) {
            printf("%ld -> ", node->score);
            node = node->forwards[i];
        }
        printf("Nil\n");
    }
}
