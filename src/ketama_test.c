/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ketama.h"
#include "utils.h"

void
case_ketama_new()
{
    struct ketama_node nodes[13] = {
        {"127.0.0.1:8000", 1, NULL, 0},
        {"127.0.0.1:8001", 1, NULL, 0},
        {"127.0.0.1:8002", 1, NULL, 0},
        {"127.0.0.1:8003", 1, NULL, 0},
        {"127.0.0.1:8004", 1, NULL, 0},
        {"127.0.0.1:8005", 1, NULL, 0},
        {"127.0.0.1:8006", 1, NULL, 0},
        {"127.0.0.1:8007", 1, NULL, 0},
        {"127.0.0.1:8008", 1, NULL, 0},
        {"127.0.0.1:8009", 1, NULL, 0},
        {"127.0.0.1:8010", 1, NULL, 0},
        {"127.0.0.1:8011", 1, NULL, 0},
        {"127.0.0.1:8022", 5, NULL, 0},
    };
    struct ketama_ring *ring = ketama_ring_new(nodes, 13);
    assert(ring->nodes != NULL);
    assert(ring->len == 12 + 5);
    ketama_ring_free(ring);
}

void
case_ketama_get()
{
    struct ketama_node nodes[5] = {
        {"192.168.0.1:9527", 1, NULL, 0},
        {"192.168.0.2:9527", 1, NULL, 0},
        {"192.168.0.3:9527", 2, NULL, 0},
        {"192.168.0.4:9527", 2, NULL, 0},
        {"192.168.0.5:9527", 4, NULL, 0},
    };
    struct ketama_ring *ring = ketama_ring_new(nodes, 5);
    assert(ring->len == 1+1+2+2+4);
    assert(ring->nodes != NULL);

    /* consistence testing */
    char key[11];
    srand(time(NULL));
    random_str(key, 10);
    struct ketama_node node = ketama_node_sget(ring, key);
    int i;
    for (i = 0; i < 1000; i++)
        assert(strcmp(node.key, ketama_node_sget(ring, key).key) == 0);

    ketama_ring_free(ring);
}
