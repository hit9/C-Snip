/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ketama.h"
#include "utils.h"

static uint32_t
ketama_hash(char *key, size_t len)
{
    return jenkins_hash(key, len) & 0x7fffffff;
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
    int size = ring->size;

    if (size == 0)
        return ketama_node_null;

    if(size == 1)
        return nodes[0];

    int left = 0, right = size - 1;
    int mid;
    int digest = ketama_hash(key, strlen(key));

    while (left < right) {
        mid = (left + right) / 2;

        if (nodes[mid].digest < digest) {
            left = mid + 1;
        } else if (nodes[mid].digest > digest) {
            right = mid - 1;
        } else {
            return nodes[mid];
        }
    }

    if (right < 0) right = 0;
    if (left > size - 1) left = size - 1;

    if (abs(nodes[left].digest - digest) > abs(nodes[right].digest - digest))
        return nodes[right];
    return nodes[left];
}
