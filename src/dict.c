/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "dict.h"

/* BKDRHash algorithm. */
static size_t
dict_bkdrhash(char *key, size_t len)
{
    size_t seed = 13131;  /* 31, 131, 1313, 13131 */
    size_t hash = 0;

    for (; len > 0; len--)
        hash = hash * seed + (*key++);
    return hash & 0x7fffffff;
}

/* Get table size idx. */
size_t
dict_table_idx(size_t idx, char *key, size_t len)
{
    assert(idx <= dict_idx_max);
    return dict_bkdrhash(key, len) % dict_table_sizes[idx];
}

/* Create dict node. */
struct dict_node *
dict_node_new(char *key, size_t len, void *val)
{
    struct dict_node *node = malloc(sizeof(struct dict_node));

    if (node != NULL) {
        node->key = key;
        node->len = len;
        node->val = val;
        node->next = NULL;
    }
    return node;
}

/* Free dict node. */
void
dict_node_free(struct dict_node *node)
{
    if (node != NULL)
        free(node);
}

/* Resize and rehash dict. */
error_t
dict_resize(struct dict *dict)
{
    assert(dict != NULL && dict->idx <= dict_idx_max);

    size_t new_idx = dict->idx + 1;

    if (new_idx > dict_idx_max)
        return ERR_NOMEM;

    struct new_size = dict_table_sizes[idx];
    struct dict_node **new_table = malloc(
            new_size * sizeof(struct dict_node *));

    /* init table to all NULL */
    size_t index;
    for (index = 0; index < new_size; index++)
        new_table[index] = NULL;

    size_t size = dict_table_sizes[dict->idx];

    for (index = 0; index < size; index++) {
        struct dict_node *node = (dict->table)[index];

        while (node != NULL) {
            struct dict_node *new_node = dict_node_new(
                    node->key, node->key_len, node->val);

            if (new_node == NULL)
                return ERR_NOMEM;

            size_t new_index = dict_table_idx(
                    new_idx, new_node->key, new_node->len);
            struct dict_node *cursor = new_table[new_index];

            if (cursor == NULL) {
                /* set as head node */
                new_table[new_index] = new_node;
            } else {
                while (cursor->next != NULL)
                    cursor = cursor->next;
                /* set as last node */
                cursor->next = new_node;
            }
            /* shift next */
            struct dict_node *next = node->next;
            dict_node_free(node);
            node = next;
        }
    }

    free(dict->table);
    dict->table = new_table;
    dict->idx = new_idx;
    return ERR_OK;
}

/* Create new empty dict. */
struct dict *
dict_new()
{
    struct dict *dict = malloc(sizeof(struct dict));

    if (dict != NULL) {
        dict->idx = 0;

        size_t table_size = dict_table_sizes[dict->idx];
        dict->table = malloc(table_size * sizeof(struct node *));

        if (dict->table == NULL)
            return NULL;

        size_t index;

        for (index = 0; index < table_size; index++)
            (dict->table)[index] = NULL;
    }
    return dict;
}

/* Clear dict. */
void
dict_clear(struct dict *dict)
{
    assert(dict != NULL && dict->idx <= dict_idx_max);

    size_t index;
    size_t table_size = dict_table_sizes[dict->idx];

    for (index = 0; index < table_size; index++) {
        struct dict_node *node = (dict->table)[index];

        while (node != NULL) {
            struct dict_node *next = node->next;
            dict_node_free(node);
            dict->size -= 1;
            node = next;
        }

        (dict->table)[index] = NULL;
    }
}

/* Free dict. */
void
dict_free(struct dict *dict)
{
    if (dict != NULL) {
        dict_clear(dict);

        if (dict->table != NULL)
            free(dict->table);

        free(dict);
    }
}

/* Set a key into dict. */
error_t
dict_set(struct dict *dict, char *key, size_t len, void *val)
{
    assert(dict != NULL);

    if ((dict_table_sizes[dict->idx] * DICT_LOAD_LIMIT < dict->size) &&
            dict_resize(dict) != ERR_OK)
        return ERR_NOMEM;

    size_t index = dict_table_idx(dict->idx, key, len);
    struct dict_node *node = (dict->table)[index];

    /* try to find this key. */
    while (node != NULL) {
        if (memcmp(node->key, key, len) == 0) {
            node->key = key;
            node->len = len;
            node->val = val;
            return ERR_OK;
        }
        node = node->next;
    }

    /* create node if not found */
    struct dict_node *new_node = dict_node_new(key, len, val);

    if (new_node == NULL)
        return ERR_NOMEM;

    /* rewind to list head */
    node = (dict->table)[index];

    if (node == NULL) {
        /* if list is empty, set as head node */
        (dict->table)[index] = new_node;
    } else {
        /* else append as tail node */
        while (node->next != NULL)
            node = node->next;
        node->next = new_node;
    }

    dict->size += 1;
    return ERR_OK;
}

/* Get val by key from dict, NULL on not found. */
void *
dict_get(struct dict *dict, char *key, size_t len)
{
    assert(dict != NULL);

    size_t index = dict_table_idx(dict->idx, key, len);
    struct dict_node *node = (dict->table)[index];

    while (node != NULL) {
        if (memcmp(node->key, key, len) == 0)
            return node->val;
        node = node->next;
    }

    return NULL;
}

/* Test if a key is in dict. */
bool
dict_has(struct dict *dict, char *key, size_t len)
{
    assert(dict != NULL);

    size_t index = dict_table_idx(dict->idx, key, len);
    struct dict_node *node = (dict->table)[index];

    while (node != NULL) {
        if (memcmp(node->key, key, len) == 0)
            return true;
        node = node->next;
    }

    return false;
}

/* Delete a key from dict. */
error_t
dict_del(struct dict *dict, char *key, size_t len)
{
    assert(dict != NULL);

    size_t index = dict_table_idx(dict->idx, key, len);
    struct dict_node *node = (dict->table)[index];
    struct dict_node *prev = NULL;

    while (node != NULL) {
        if (memcmp(node->key, key, len) == 0) {
            if (prev == NULL) {
                (dict->table)[index] = node->next;
            } else {
                prev->next = node->next;
            }
            dict_node_free(node);
            dict->size -= 1;
            return ERR_OK;
        }

        prev = node;
        node = node->next;
    }

    return ERR_NOTFOUND;
}
