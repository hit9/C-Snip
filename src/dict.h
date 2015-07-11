/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic sized list-based hashtable implementation.
 */

#ifndef _CW_DICT_H
#define _CW_DICT_H 1

#include <stdint.h>
#include "bool.h"
#include "errors.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define DICT_LOAD_LIMIT     0.75  /* load factor */

#define dict()              dict_new()
#define dict_iter(dict)     dict_iter_new(dict)

struct dict_node {
    char *key;                 /* key string address */
    size_t len;                /* key string length */
    void *val;                 /* value data */
    struct dict_node *next;    /* next node */
};

struct dict {
    size_t idx;                /* index in table sizes */
    size_t size;               /* dict size */
    struct dict_node **table;  /* node table */
};

struct dict_iter {
    struct dict *dict;         /* dict to iterate */
    size_t index;              /* current table index */
    struct dict_node *node;    /* current dict node */
};

static size_t dict_table_sizes[] = {
    7, 17, 37, 79, 163, 331, 673, 1361, 2729,
    5471, 10949, 21911, 43853, 87719, 175447,
    350899, 701819, 1403641, 2807303, 5614657,
    11229331, 44917381, 89834777, 179669557,
    359339171, 718678369, 1437356741, 2147483647,
};

static size_t dict_idx_max = sizeof(dict_table_sizes)/\
                             sizeof(dict_table_sizes[0])-1;  /* 28 */

struct dict *dict_new(void);
void dict_clear(struct dict *dict);
void dict_free(struct dict *dict);
error_t dict_set(struct dict *dict, char *key, size_t len, void *val);
void *dict_get(struct dict *dict, char *key, size_t len);
void *dict_pop(struct dict *dict, char *key, size_t len);
bool dict_has(struct dict *dict, char *key, size_t len);
struct dict_iter *dict_iter_new(struct dict *dict);
void dict_iter_free(struct dict_iter *iter);
struct dict_node *dict_iter_next(struct dict_iter *iter);
void dict_iter_rewind(struct dict_iter *iter);

#if defined(__cplusplus)
}
#endif

#endif
