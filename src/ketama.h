/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Ketama consistent hashing implementation.
 */

#ifndef _CW_KETAMA_H
#define _CW_KETAMA_H 1

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define ketama_ring(nodes, size)    ketama_ring_new(nodes, size)

/* Note ketama ring's `nodes` and its `length` is not the orignal parameter
 * passed in. */
struct ketama_ring {
    size_t len;                  /* hash ring nodes array length */
    struct ketama_node *nodes;   /* hash ring nodes array */
};

struct ketama_node {
    char *key;            /* node key */
    unsigned int weight;  /* node weight */
    void *data;           /* user data */
    long idata;           /* user long typed data */
    size_t idx;           /* node idx in origin array */
    uint32_t hash;        /* hash value in the ring */
};

static struct ketama_node ketama_node_null = {NULL, 0, NULL, 0};

struct ketama_ring *ketama_ring_new(struct ketama_node *nodes, size_t len);
void ketama_ring_free(struct ketama_ring *ring);
struct ketama_node ketama_node_get(struct ketama_ring *ring, char *key, size_t key_len);
struct ketama_node ketama_node_sget(struct ketama_ring *ring, char *key);

#if defined(__cplusplus)
}
#endif
#endif
