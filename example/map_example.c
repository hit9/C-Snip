// cc map_example.c map.c

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

int main(int argc, const char *argv[])
{
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
    /* free the map */
    map_free(m);
    return 0;
}
