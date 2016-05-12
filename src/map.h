/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic sized simple open-addressing hashtable implementation.
 * deps: None
 */

#ifndef _CW_MAP_H
#define _CW_MAP_H 1

#include <stdint.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define MAP_LOAD_LIMIT 0.72            /* load factor */
#define MAP_CAP_MAX 1024 * 1024 * 1024 /* 1GB */
#define MAP_CAP_INIT 16                /* init table size: must be 2** */

#define map() map_new()
#define map_iter(m) map_iter_new(m)
#define map_each(iter, node) while (((node) = map_iter_next((iter))) != NULL)

enum {
    MAP_OK = 0,     /* operation is ok */
    MAP_ENOMEM = 1, /* no memory error */
};

struct map_node {
    char *key;  /* key string */
    size_t len; /* key length */
    void *val;  /* value data*/
};

struct map {
    size_t cap;             /* map capacity */
    size_t len;             /* map length */
    struct map_node *table; /* node table */
};

struct map_iter {
    struct map *m; /* map to iterate */
    size_t i;      /* current table index */
};

struct map *map_new(void);
void map_free(struct map *m);
void map_clear(struct map *m);                                 /* O(1) */
size_t map_len(struct map *m);                                 /* O(1) */
size_t map_cap(struct map *m);                                 /* O(1) */
int map_set(struct map *m, char *key, void *val);              /* O(1) */
void *map_get(struct map *m, char *key);                       /* O(1) */
int map_has(struct map *m, char *key);                         /* O(1) */
void *map_pop(struct map *m, char *key);                       /* O(1) */
int map_iset(struct map *m, char *key, size_t len, void *val); /* O(1) */
void *map_iget(struct map *m, char *key, size_t len);          /* O(1) */
int map_ihas(struct map *m, char *key, size_t len);            /* O(1) */
void *map_ipop(struct map *m, char *key, size_t len);          /* O(1) */
struct map_iter *map_iter_new(struct map *m);
void map_iter_free(struct map_iter *iter);
struct map_node *map_iter_next(struct map_iter *iter);
void map_iter_rewind(struct map_iter *iter);

#if defined(__cplusplus)
}
#endif

#endif
