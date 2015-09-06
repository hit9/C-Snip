/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "ketama.h"

void
case_ketama_new()
{
    struct ketama_node nodes[10] = {
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
    };

    struct ketama_ring *ring = ketama_ring_new(nodes, 10);
    ketama_ring_free(ring);
}
