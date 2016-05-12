/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>

#include "map.h"
#include "strings.h"

void case_map_set() {
    struct map *m = map();
    char *key = "key", *val = "val";
    assert(map_set(m, key, val) == MAP_OK);
    assert(map_len(m) == 1);
    assert(map_get(m, key) == val);
    /* set multiple times */
    int i;
    for (i = 0; i < 10000; i++) {
        char key[11];
        char val[21];
        strings_rand(key, 10);
        strings_rand(val, 20);
        assert(map_set(m, key, val) == MAP_OK);
        assert(map_get(m, key) == val);
    }
    map_free(m);
}

void case_map_get() {
    struct map *m = map();
    char *key = "key", *val = "val";
    assert(map_set(m, key, val) == MAP_OK);
    assert(map_len(m) == 1);
    assert(map_get(m, key) == val);
    assert(map_get(m, "not exist") == NULL);
    map_free(m);
}

void case_map_pop() {
    struct map *m = map();
    char *key = "key", *val = "val";
    assert(map_set(m, key, val) == MAP_OK);
    assert(map_len(m) == 1);
    assert(map_pop(m, key) == val);
    assert(map_len(m) == 0);
    assert(map_pop(m, "not-exist") == NULL);
    map_free(m);
}

void case_map_has() {
    struct map *m = map();
    char *key = "key", *val = "val";
    assert(map_set(m, key, val) == MAP_OK);
    assert(!map_has(m, "not exist"));
    assert(map_has(m, key));
    map_free(m);
}

void case_map_clear() {
    struct map *m = map();
    assert(map_set(m, "key1", "val1") == MAP_OK);
    assert(map_set(m, "key2", "val2") == MAP_OK);
    assert(map_set(m, "key3", "val3") == MAP_OK);
    assert(map_set(m, "key4", "val4") == MAP_OK);
    assert(map_set(m, "key5", "val5") == MAP_OK);
    assert(map_len(m) == 5);
    map_clear(m);
    assert(map_len(m) == 0);
    map_free(m);
}

void case_map_iter() {
    struct map *m = map();
    char *key1 = "key1";
    char *key2 = "key2";
    char *key3 = "key3";
    char *key4 = "key4";
    char *key5 = "key5";
    char *key6 = "key6";
    assert(map_set(m, key1, "val1") == MAP_OK);
    assert(map_set(m, key2, "val2") == MAP_OK);
    assert(map_set(m, key3, "val3") == MAP_OK);
    assert(map_set(m, key4, "val4") == MAP_OK);
    assert(map_set(m, key5, "val5") == MAP_OK);
    assert(map_set(m, key6, "val6") == MAP_OK);
    struct map_iter *iter = map_iter(m);
    assert(map_iter_next(iter) != NULL);
    assert(map_iter_next(iter) != NULL);
    assert(map_iter_next(iter) != NULL);
    assert(map_iter_next(iter) != NULL);
    assert(map_iter_next(iter) != NULL);
    assert(map_iter_next(iter) != NULL);
    assert(map_iter_next(iter) == NULL);
    map_iter_free(iter);
    map_free(m);
}
