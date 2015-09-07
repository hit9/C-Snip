/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "ketama.h"

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
        {"127.0.0.1:8022", 1, NULL, 0},
    };

    struct ketama_ring *ring = ketama_ring_new(nodes, 13);

    int i;
    for (i = 0; i < 13; i++) {
        printf("%ld\n", ring->nodes[i].digest);
    }

    printf("%s\n", ketama_node_get(ring, "key1").key);
    printf("%s\n", ketama_node_get(ring, "kzy2").key);
    printf("%s\n", ketama_node_get(ring, "k2y3").key);
    printf("%s\n", ketama_node_get(ring, "kxxessdd4").key);
    printf("%s\n", ketama_node_get(ring, "su").key);
    printf("%s\n", ketama_node_get(ring, "suyh").key);
    printf("%s\n", ketama_node_get(ring, "yuyy").key);
    printf("%s\n", ketama_node_get(ring, "oo899o").key);
    printf("%s\n", ketama_node_get(ring, "www").key);
    printf("%s\n", ketama_node_get(ring, "3<Plug>(multiple-cursors-apply)").key);
    printf("%s\n", ketama_node_get(ring, "1").key);
    printf("%s\n", ketama_node_get(ring, "2").key);
    printf("%s\n", ketama_node_get(ring, "3").key);
    printf("%s\n", ketama_node_get(ring, "88888888888sssssssss").key);
    printf("%s\n", ketama_node_get(ring, "xxxx").key);
    printf("%s\n", ketama_node_get(ring, "xxxx8").key);
    printf("%s\n", ketama_node_get(ring, "xxxxss9").key);
    printf("%s\n", ketama_node_get(ring, "xxxsssx9").key);
    printf("%s\n", ketama_node_get(ring, "xjxxss9").key);
    printf("%s\n", ketama_node_get(ring, "xs9").key);
    printf("%s\n", ketama_node_get(ring, "xxss9").key);
    printf("%s\n", ketama_node_get(ring, "xxbabss9").key);
    printf("%s\n", ketama_node_get(ring, "xxxx27hjsss9").key);
    printf("%s\n", ketama_node_get(ring, "xss9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxssia9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxssaaa9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxssbbb9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxszzs9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxsooos9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxs00s9").key);
    printf("%s\n", ketama_node_get(ring, "xxxxss9129").key);
    printf("%s\n", ketama_node_get(ring, "xxxxss229").key);
    ketama_ring_free(ring);
}
