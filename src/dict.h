/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic sized list-based hashtable implementation.
 * deps: None
 */

#ifndef __DICT_H__
#define __DICT_H__

#include <stdint.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define DICT_LOAD_LIMIT 0.72 /* load factor */
#define dict() dict_new()
#define dict_iter(dict) dict_iter_new(dict)
#define dict_each(iter, node) while (((node) = dict_iter_next((iter))) != NULL)

enum {
    DICT_OK = 0,     /* operation is ok */
    DICT_ENOMEM = 1, /* no memory error */
};

struct dict_node {
    char *key;              /* key string */
    size_t len;             /* key length will be set on `node_new` */
    void *val;              /* value data */
    struct dict_node *next; /* next node */
};

struct dict {
    size_t idx;               /* index in table sizes */
    size_t len;               /* dict length */
    struct dict_node **table; /* node table */
};

struct dict_iter {
    struct dict *dict;      /* dict to iterate */
    size_t index;           /* current table index */
    struct dict_node *node; /* current dict node */
};

struct dict *dict_new(void);
void dict_clear(struct dict *dict); /* O(N) */
void dict_free(struct dict *dict);
size_t dict_len(struct dict *dict);                    /* O(1) */
size_t dict_cap(struct dict *dict);                    /* O(1) */
int dict_set(struct dict *dict, char *key, void *val); /* O(1) */
void *dict_get(struct dict *dict, char *key);          /* O(1) */
void *dict_pop(struct dict *dict, char *key);          /* O(1) */
int dict_has(struct dict *dict, char *key);            /* O(1) */
struct dict_iter *dict_iter_new(struct dict *dict);
void dict_iter_free(struct dict_iter *iter);
struct dict_node *dict_iter_next(struct dict_iter *iter);
void dict_iter_rewind(struct dict_iter *iter);
int dict_iset(struct dict *dict, char *key, size_t len, void *val); /* O(1) */
void *dict_iget(struct dict *dict, char *key, size_t len);          /* O(1) */
void *dict_ipop(struct dict *dict, char *key, size_t len);          /* O(1) */
int dict_ihas(struct dict *dict, char *key, size_t len);            /* O(1) */

#if defined(__cplusplus)
}
#endif

#endif
