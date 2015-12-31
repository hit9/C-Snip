/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic sized simple open-addressing hashtable implementation.
 * deps: None
 */

#ifndef _CW_MAP_H
#define _CW_MAP_H 1

#if defined(__cplusplus)
extern "C" {
#endif

#define MAP_LOAD_LIMIT 0.5 /* load factor */
#define MAP_CAP_MAX 1024*1024*1024 /* 1GB */
#define MAP_CAP_INIT 7

#define map() map_new()

enum {
    MAP_OK = 0,     /* operation is ok */
    MAP_ENOMEM = 1, /* no memory error */
};

struct map_node {
    char *key;   /* key string */
    size_t len;  /* key length */
    void *val;   /* value data*/
};

struct map {
    size_t cap;  /* map capacity */
    size_t len;  /* map length */
    struct map_node *table; /* node table */
};

struct map *map_new(void);
void map_free(struct map *m);
void map_clear(struct map *m);
size_t map_len(struct map *m);
size_t map_cap(struct map *m);
int map_set(struct map *m, char *key, void *val);
void *map_get(struct map *m, char *key);
int map_has(struct map *m, char *key);
void *map_pop(struct map *m, char *key);
int map_iset(struct map *m, char *key, size_t len, void *val);
void *map_iget(struct map *m, char *key, size_t len);
int map_ihas(struct map *m, char *key, size_t len);
void *map_ipop(struct map *m, char *key, size_t len);

#if defined(__cplusplus)
}
#endif

#endif
