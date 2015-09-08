/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>
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
    return ((struct ketama_node *)node_a)->hash - \
        ((struct ketama_node *)node_b)->hash;
}

/* Create ketama hash ring from nodes array. */
struct ketama_ring *
ketama_ring_new(struct ketama_node *nodes, size_t len)
{
    if (len > 0)
        assert(nodes != NULL);

    struct ketama_ring *ring = malloc(sizeof(struct ketama_ring));

    if (ring == NULL)
        return NULL;

    int i;

    for (i = 0, ring->len = 0; i < len; i++)
        ring->len += nodes[i].weight;

    ring->nodes = malloc(sizeof(struct ketama_node) * ring->len);

    if (ring->nodes == NULL) {
        free(ring);
        return NULL;
    }

    int j, k, digits;
    struct ketama_node node;
    unsigned int num;
    size_t key_len_max;

    for (i = 0, k = 0; i < len; i++) {
        node = nodes[i];

        for (digits = 0, num = node.weight;
                num > 0; num /= 10, ++digits);

        assert(node.key != NULL);
        assert(node.hash == 0);

        key_len_max = strlen(node.key) + digits + 1;
        char key[key_len_max];

        for (j = 0; j < node.weight; j++, k++) {
            ring->nodes[k].key = node.key;
            ring->nodes[k].weight = node.weight;
            ring->nodes[k].data = node.data;
            memset(key, 0, key_len_max);
            sprintf(key, "%s:%d", node.key, j);
            ring->nodes[k].hash = ketama_hash(key, strlen(key));
        }
    }

    qsort(ring->nodes, ring->len, sizeof(struct ketama_node), ketama_node_cmp);
    return ring;
}

/* Free ketama ring. */
void
ketama_ring_free(struct ketama_ring *ring)
{
    if (ring != NULL) {
        if (ring->nodes != NULL)
            free(ring->nodes);
        free(ring);
    }
}

/* Get node by key from ring. */
struct ketama_node
ketama_node_get(struct ketama_ring *ring, char *key, size_t key_len)
{
    assert(ring != NULL);
    assert(key != NULL);
    assert(ring->nodes != NULL);

    struct ketama_node *nodes = ring->nodes;
    size_t len = ring->len;

    if (len == 0)
        return ketama_node_null;

    if (len == 1)
        return nodes[0];

    int left = 0, right = len - 1, mid;
    uint32_t hash = ketama_hash(key, key_len);

    while (left < right) {
        mid = (left + right) / 2;

        if (nodes[mid].hash < hash) {
            left = mid + 1;
        } else if (nodes[mid].hash > hash) {
            right = mid - 1;
        } else {
            return nodes[mid];
        }
    }

    if (left > len - 1) left = len - 1;
    if (right < 0) right = 0;

    if (abs(nodes[left].hash - hash) >
            abs(nodes[right].hash - hash))
        return nodes[right];
    return nodes[left];
}

/* Get node by key from ring. */
struct ketama_node
ketama_node_sget(struct ketama_ring *ring, char *key)
{
    return ketama_node_get(ring, key, strlen(key));
}
