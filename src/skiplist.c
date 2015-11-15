/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>

#include "skiplist.h"

/* Get random level between 0 and level_max. */
static int skiplist_rand_level(void)
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
skiplist_node_new(int level, void *data)
{
    assert(level > 0);

    struct skiplist_node *node = malloc(sizeof(struct skiplist_node));

    if (node != NULL) {
        node->data = data;
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
    struct skiplist *skiplist = malloc(sizeof(struct skiplist));

    if (skiplist != NULL) {
        skiplist->len = 0;
        skiplist->level = 1;
        skiplist->cmp = cmp;
        skiplist->head = skiplist_node_new(SKIPLIST_LEVEL_MAX, NULL);
        if (skiplist->head == NULL) {
            free(skiplist);
            return NULL;
        }
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
        skiplist_pop(skiplist);
}

/* Get skiplist length. */
size_t
skiplist_len(struct skiplist *skiplist)
{
    assert(skiplist != NULL);
    return skiplist->len;
}

/* Push data to skiplist. */
int
skiplist_push(struct skiplist *skiplist, void *data)
{
    assert(skiplist != NULL && skiplist->head != NULL);

    struct skiplist_node *update[SKIPLIST_LEVEL_MAX];
    struct skiplist_node *node = skiplist->head;
    int i;

    for (i = skiplist->level - 1; i >= 0; i--) {
        while (node->forwards[i] != NULL &&
                (skiplist->cmp)(node->forwards[i]->data, data) < 0)
            node = node->forwards[i];
        update[i] = node;
    }

    int level = skiplist_rand_level();

    if (level > skiplist->level) {
        for (i = skiplist->level; i < level; i++)
            update[i] = skiplist->head;
        skiplist->level = level;
    }

    node = skiplist_node_new(level, data);

    if (node == NULL)
        return SKIPLIST_ENOMEM;

    for (i = 0; i < level; i++) {
        node->forwards[i] = update[i]->forwards[i];
        update[i]->forwards[i] = node;
    }

    skiplist->len += 1;
    return SKIPLIST_OK;
}

/* Get top data, NULL on empty. */
void *
skiplist_top(struct skiplist *skiplist)
{
    assert(skiplist != NULL && skiplist->head != NULL);

    if (skiplist->len == 0)
        return NULL;
    return skiplist->head->forwards[0]->data;
}

/* Pop top data, NULL on empty. */
void *
skiplist_pop(struct skiplist *skiplist)
{
    assert(skiplist != NULL && skiplist->head != NULL);

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

    void *data = node->data;
    skiplist_node_free(node);
    skiplist->len -= 1;
    return data;
}
