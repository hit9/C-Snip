/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Ketama consistent hashing implementation.
 */

#ifndef _CW_KETAMA_H
#define _CW_KETAMA_H 1

#if defined(__cplusplus)
extern "C" {
#endif

struct ketama_ring {
    int size;                    /* hash ring size */
    struct ketama_node *nodes;   /* hash ring nodes array */
};

struct ketama_node {
    char *key;      /* node key */
    int weight;     /* node weight */
    void *data;     /* user data */
    int digest;     /* hash digest in the ring */
};

static struct ketama_node ketama_node_null = {NULL, 0, NULL, 0};

struct ketama_ring *ketama_ring_new(struct ketama_node *nodes, int size);
void ketama_ring_free(struct ketama_ring *ring);
struct ketama_node ketama_node_get(struct ketama_ring *ring, char *key);

#if defined(__cplusplus)
}
#endif
#endif
