// cc ketama_example.c ketama.c md5.c

#include <stdio.h>
#include <string.h>
#include "ketama.h"

int main(int argc, const char *argv[])
{
    /* ketama node array */
    struct ketama_node nodes[4] = {
        {"127.0.0.1:8000", 1, "server a"},
        {"127.0.0.1:8001", 1, "server b"},
        {"127.0.0.1:8002", 1, "server c"},
        {"127.0.0.1:8003", 1, "server d"},
    };
    /* create a ketama ring of 4 nodes */
    struct ketama_ring *ring = ketama_ring(nodes, 4);
    /* get node by null-terminated key */
    struct ketama_node node = ketama_node_sget(ring, "key");
    printf("get a node by 'key': %s %s\n", node.key, node.data);
    /* get again, consistence hashing */
    node = ketama_node_sget(ring, "key");
    printf("get again by 'key': %s %s\n", node.key, node.data);
    /* free the ring */
    ketama_ring_free(ring);
    return 0;
}
