/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ketama.h"
#include "strings.h"

void case_ketama_balance() {
    struct ketama_node nodes[13] = {
        {"127.0.0.1:8000", 1},
        {"127.0.0.1:8001", 1},
        {"127.0.0.1:8002", 1},
        {"127.0.0.1:8003", 1},
        {"127.0.0.1:8004", 1},
        {"127.0.0.1:8005", 1},
        {"127.0.0.1:8006", 1},
        {"127.0.0.1:8007", 1},
        {"127.0.0.1:8008", 1},
        {"127.0.0.1:8009", 1},
        {"127.0.0.1:8010", 1},
        {"127.0.0.1:8011", 1},
        {"127.0.0.1:8012", 1},
    };
    struct ketama_ring *ring = ketama_ring_new(nodes, 13);
    assert(ring->nodes != NULL);
    assert(ring->len == 13 * 160);

    int i;
    for (i = 0; i < 2600; i++) {
        char key[11];
        strings_rand(key, 10);
        struct ketama_node *node = ketama_node_get(ring, key);
        nodes[node->idx].idata += 1;
    }

    for (i = 0; i < 13; i++)
        assert(nodes[i].idata > 150 && nodes[i].idata < 300);

    ketama_ring_free(ring);
}

void case_ketama_consistence() {
    /* consistence testing */
    struct ketama_node nodes[5] = {
        {"192.168.0.1:9527", 1},
        {"192.168.0.2:9527", 1},
        {"192.168.0.3:9527", 2},
        {"192.168.0.4:9527", 2},
        {"192.168.0.5:9527", 4},
    };
    struct ketama_ring *ring = ketama_ring_new(nodes, 5);
    assert(ring->len == (1 + 1 + 2 + 2 + 4) * 160);
    assert(ring->nodes != NULL);

    char key[11];
    srand(time(NULL));
    strings_rand(key, 10);
    struct ketama_node *node = ketama_node_get(ring, key);
    int i;
    for (i = 0; i < 1000; i++) {
        assert(strcmp(node->key, ketama_node_get(ring, key)->key) == 0);
    }

    ketama_ring_free(ring);
}
