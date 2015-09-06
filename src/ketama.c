/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ketama.h"

/* Jenkins Hash function
 * https://en.wikipedia.org/wiki/Jenkins_hash_function */
static uint32_t
ketama_hash(char *key, size_t len)
{
    uint32_t hash, i;

    for(hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & 0x7fffffff;
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
        assert(node.weight > 0);
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

    struct ketama_node *nodes = ring->nodes;
    int left = 0, right = ring->size, size = ring->size;
    int mid;

    if (size == 0)
        return ketama_node_null;

    int mid_digest;
    uint32_t digest = ketama_hash(key, strlen(key));

    while (1) {
        mid = (left + right) / 2;

        if (mid == size || mid == 0)
            return nodes[0];

        if (nodes[mid].digest >= digest && digest > nodes[mid - 1].digest)
            return nodes[mid];

        if (nodes[mid].digest < digest) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }

        if (left > right)
            return nodes[0];
    }
}
