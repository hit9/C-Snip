/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ketama.h"
#include "md5.h"
#include "utils.h"

static uint32_t
ketama_hash(char *key, size_t len, size_t align)
{
    assert(align < 4);
    unsigned char results[16];
    md5_signature((unsigned char*)key, (unsigned long)len, results);
    return ((uint32_t) (results[3 + align * 4] & 0xff) << 24) |
           ((uint32_t) (results[2 + align * 4] & 0xff) << 16) |
           ((uint32_t) (results[1 + align * 4] & 0xff) << 8) |
           (results[0 + align * 4] & 0xff);
}

static int
ketama_node_cmp(const void *node_a, const void *node_b)
{
    uint32_t hash_a = ((struct ketama_node *)node_a)->hash;
    uint32_t hash_b = ((struct ketama_node *)node_b)->hash;

    if (hash_a > hash_b) return 1;
    else if (hash_a < hash_b) return -1;
    else return 0;
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
        ring->len += nodes[i].weight * 160;

    ring->nodes = malloc(sizeof(struct ketama_node) * ring->len);

    if (ring->nodes == NULL) {
        free(ring);
        return NULL;
    }

    int j, k, n, digits;
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

        for (j = 0; j < node.weight * 40; j++) {
            memset(key, 0, key_len_max);
            sprintf(key, "%s-%d", node.key, j);
            for (n = 0; n < 4; n++, k++) {
                ring->nodes[k].key = node.key;
                ring->nodes[k].weight = node.weight;
                ring->nodes[k].data = node.data;
                ring->nodes[k].idata = node.idata;
                ring->nodes[k].idx = i;
                ring->nodes[k].hash = ketama_hash(key, strlen(key), n);
            }
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
    uint32_t val;

    if (len == 0)
        return ketama_node_null;

    if (len == 1)
        return nodes[0];

    int left = 0, right = len, mid;
    uint32_t hash = ketama_hash(key, key_len, 0);
    uint32_t mval, pval;

    while (1) {
        mid = (left + right) / 2;

        if (mid == len)
            return nodes[0];

        mval = nodes[mid].hash;
        pval = mid == 0 ? 0 : nodes[mid - 1].hash;

        if (hash <= mval && hash > pval)
            return nodes[mid];

        if (mval < hash) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }

        if (left > right)
            return nodes[0];
    }
}

/* Get node by key from ring. */
struct ketama_node
ketama_node_sget(struct ketama_ring *ring, char *key)
{
    return ketama_node_get(ring, key, strlen(key));
}
