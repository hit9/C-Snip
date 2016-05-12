// cc map_example.c map.c

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

int main(int argc, const char *argv[]) {
    /* allocate a new map */
    struct map *m = map();
    /* set key and values to map */
    char *key1 = "key1";
    char *key2 = "key2";
    char *val1 = "val1";
    char *val2 = "val2";
    assert(map_set(m, key1, val1) == MAP_OK);
    assert(map_set(m, key2, val2) == MAP_OK);
    /* get map length */
    assert(map_len(m) == 2);
    /* get data by key */
    assert(map_get(m, key1) == val1);
    assert(map_get(m, key2) == val2);
    /* set some key values more */
    assert(map_set(m, "key3", "val3") == MAP_OK);
    assert(map_set(m, "key4", "val4") == MAP_OK);
    assert(map_set(m, "key5", "val5") == MAP_OK);
    assert(map_set(m, "key6", "val6") == MAP_OK);
    assert(map_set(m, "key7", "val7") == MAP_OK);
    /* iterate the map */
    struct map_iter iter = {m};
    struct map_node *node = NULL;
    map_each(&iter, node) {
        printf("%s => %s\n", node->key, (char *)node->val);
    }
    /* free the map */
    map_free(m);
    return 0;
}
