/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

#define MAP_LOAD_LIMIT  0.7            /* load factor */
#define MAP_CAP_MAX     1024*1024*1024 /* 1GB */
#define MAP_CAP_INIT    16             /* init table size: must be 2** */

/* Hash function. */
static uint32_t
map_hash(char *key, size_t len)
{
    /* DJBX33A hash function from PHP */
    register int hash = 5381;
    for (; len >= 8; len -= 8) {
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
    }
    switch (len) {
        case 7: hash = ((hash << 5) + hash) + *key++;
        case 6: hash = ((hash << 5) + hash) + *key++;
        case 5: hash = ((hash << 5) + hash) + *key++;
        case 4: hash = ((hash << 5) + hash) + *key++;
        case 3: hash = ((hash << 5) + hash) + *key++;
        case 2: hash = ((hash << 5) + hash) + *key++;
        case 1: hash = ((hash << 5) + hash) + *key++; break;
        case 0: break;
    }
    return hash;
}

/* If two key equals. */
int
map_keycmp(char *key1, size_t len1, char *key2, size_t len2)
{
    if (len1 == len2 && (memcmp(key1, key2, len1) == 0))
        return 1;
    return 0;
}

/* Create a map. */
struct map *
map_new(void)
{
    struct map *m = malloc(sizeof(struct map));

    if (m != NULL) {
        m->cap = 0;
        m->len = 0;
        m->table = NULL;
    }
    return m;
}

/* Free map. */
void
map_free(struct map *m)
{
    if (m != NULL) {
        if (m->table != NULL)
            free(m->table);
        free(m);
    }
}

/* Clear map. */
void
map_clear(struct map *m)
{
    assert(m != NULL);
    if (m->table != NULL)
        free(m->table);
    m->cap = 0;
    m->len = 0;
}

/* Resize and rehash map. */
int
map_resize(struct map *m)
{
    assert(m != NULL);

    /* double sized cap */
    size_t cap = m->cap * 2;

    /* validate new cap */
    if (cap < 1)
        cap = MAP_CAP_INIT;

    if (cap > MAP_CAP_MAX)
        return MAP_ENOMEM;

    /* create new table */
    struct map_node *table = malloc(cap * sizeof(struct map_node));

    if (table == NULL)
        return MAP_ENOMEM;

    /* init all keys to NULL */
    int i;
    for (i = 0; i < cap; i++)
        table[i].key = NULL;

    /* rehash old into new table */
    int mask = cap - 1;
    for (i = 0; i < m->cap; i++) {
        struct map_node *node = &m->table[i];

        if (node->key == NULL)
            continue;

        int j = map_hash(node->key, node->len) & mask;
        for(;; j = (j + 1) & mask) {
            if (table[j].key != NULL)
                continue;
            table[j].key = node->key;
            table[j].len = node->len;
            table[j].val = node->val;
            break;
        }
    }
    free(m->table);
    m->table = table;
    m->cap = cap;
    return MAP_OK;
}

/* Get map length. */
size_t
map_len(struct map *m)
{
    assert(m != NULL);
    return m->len;
}

/* Get map capacity. */
size_t
map_cap(struct map *m)
{
    assert(m != NULL);
    return m->cap;
}

/* Set a key into map. */
int
map_iset(struct map *m, char *key, size_t len, void *val)
{
    assert(m != NULL);
    assert(key != NULL);

    /* if require resize */
    if ((m->cap * MAP_LOAD_LIMIT < m->len ||
                m->cap < MAP_CAP_INIT) &&
            map_resize(m) != MAP_OK)
        return MAP_ENOMEM;

    /* try to find this key */
    int mask = m->cap - 1;
    size_t i = map_hash(key, len) & mask;

    for (;; i = (i + 1) & mask) {
        struct map_node *node = &m->table[i];
        if (node->key == NULL) {
            node->key = key;
            node->len = len;
            node->val = val;
            m->len++;
            return MAP_OK;
        }
        if (map_keycmp(node->key, node->len, key, len)) {
            node->val = val;
            return MAP_OK;
        }
    }
}

/* Set a NULL-terminated key into map. */
int
map_set(struct map *m, char *key, void *val)
{
    return map_iset(m, key, strlen(key), val);
}

/* Get map node by key. */
struct map_node *
map_get_node(struct map *m, char *key, size_t len)
{
    int mask = m->cap - 1;
    size_t i = map_hash(key, len) & mask;

    for (;; i = (i + 1) & mask) {
        struct map_node *node = &m->table[i];
        if (node->key != NULL &&
                map_keycmp(node->key, node->len, key, len))
            return node;
    }
    return NULL;
}

/* Get val by key from map, NULL on not found. */
void *
map_iget(struct map *m, char *key, size_t len)
{
    assert(m != NULL);
    assert(key != NULL);

    struct map_node *node = map_get_node(m, key, len);
    if (node != NULL)
        return node->val;
    return NULL;
}

/* Get val by NULL-terminated key from map, NULL on not found. */
void *
map_get(struct map *m, char *key)
{
    return map_iget(m, key, strlen(key));
}

/* Test if a key is in map. */
int
map_ihas(struct map *m, char *key, size_t len)
{
    assert(m != NULL);
    assert(key != NULL);

    struct map_node *node = map_get_node(m, key, len);
    if (node != NULL)
        return 1;
    return 0;
}

/* Test if a key is in map by a NULL-terminated key. */
int
map_has(struct map *m, char *key)
{
    return map_ihas(m, key, strlen(key));
}

/* Pop a key from map, NULL on not found. */
void *
map_ipop(struct map *m, char *key, size_t len)
{
    assert(m != NULL);
    assert(key != NULL);

    struct map_node *node = map_get_node(m, key, len);
    if (node != NULL) {
        node->key = NULL;
        m->len--;
        return node->val;
    }
    return NULL;
}

/* Pop a key from map by NULL-terminated key, NULL on not found. */
void *
map_pop(struct map *m, char *key)
{
    return map_ipop(m, key, strlen(key));
}

/* Create map iter. */
struct map_iter *
map_iter_new(struct map *m)
{
    assert(m != NULL);
    struct map_iter *iter = malloc(sizeof(struct map_iter));

    if (iter != NULL) {
        iter->m = m;
        iter->i = 0;
    }
    return iter;
}

/* Free map iter. */
void
map_iter_free(struct map_iter *iter)
{
    if (iter != NULL)
        free(iter);
}

/* Get next. */
struct map_node *
map_iter_next(struct map_iter *iter)
{
    assert(iter != NULL && iter->m != NULL);

    struct map *m = iter->m;

    if (m->table == NULL)
        return NULL;

    for (; iter->i < m->cap; iter->i++) {
        struct map_node *node = &m->table[iter->i];
        if (node->key != NULL) {
            iter->i++;
            return node;
        }
    }
    return NULL;
}

/* Rewind map iter. */
void
map_iter_rewind(struct map_iter *iter)
{
    assert(iter != NULL);
    iter->i = 0;
}
