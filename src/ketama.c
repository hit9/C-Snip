/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ketama.h"

static int
ketama_hash(char *key, size_t len)
{
    size_t seed = 13131;  /* 31, 131, 1313, 13131 */
    size_t hash = 0;

    for (; len > 0; len--)
        hash = hash * seed + (*key++);
    int val = hash & 0x7fffffff;
    return ((val << 24) | (val << 16) | (val << 8) | val) >> 0;
}

static int
ketama_node_cmp(const void *node_a, const void *node_b)
{
    return ((struct ketama_node *)node_a)->digest - \
        ((struct ketama_node *)node_b)->digest;
}

struct ketama_ring *
ketama_ring_new(struct ketama_node *nodes, int size)
{
    assert(size >= 0);

    if (size > 0)
        assert(nodes != NULL);

    struct ketama_ring *ring = malloc(sizeof(struct ketama_ring));

    if (ring == NULL)
        return NULL;

    ring->nodes = malloc(sizeof(struct ketama_node) * size);

    if (ring->nodes == NULL) {
        free(ring);
        return NULL;
    }

    int i;
    struct ketama_node node;

    for (i = 0; i < size; i++) {
        node = nodes[i];
        assert(node.key != NULL);
        node.digest = ketama_hash(node.key, strlen(node.key));
        ring->nodes[i] = node;
    }

    qsort(ring->nodes, size, sizeof(struct ketama_node), ketama_node_cmp);
    ring->size = size;
    return ring;
}

void
ketama_ring_free(struct ketama_ring *ring)
{
    if (ring != NULL) {
        if (ring->nodes != NULL)
            free(ring->nodes);
        free(ring);
    }
}

struct ketama_node
ketama_node_get(struct ketama_ring *ring, char *key)
{
    assert(key != NULL);
    assert(ring != NULL);
    assert(ring->nodes != NULL);
    assert(ring->size >= 0);

    if (ring->size == 0)
        return ketama_node_null;

    int digest = ketama_hash(key, strlen(key));
    int left = 0, right = ring->size - 1;
    int middle;

    struct ketama_node *nodes = ring->nodes;

    if (digest >= nodes[right].digest)
        return nodes[right];

    if (digest <= nodes[left].digest)
        return nodes[left];

    while (left <= right) {
        middle = (left + right) / 2;

        if (nodes[middle].digest > digest) {
            right = middle - 1;
        } else if (nodes[middle].digest < digest) {
            left = middle + 1;
        } else {
            return nodes[middle];
        }
    }

    if (abs(nodes[left].digest - digest) > abs(nodes[right].digest - digest))
        return nodes[right];
    return nodes[left];
}
