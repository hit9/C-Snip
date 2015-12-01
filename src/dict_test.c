/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>
#include "test.h"
#include "dict.h"

void
case_dict_set()
{
    struct dict *dict = dict();
    char *key = "key", *val = "val";
    assert(dict_set(dict, key, val) == DICT_OK);
    assert(dict_len(dict) == 1);
    char *val_ = "val_";
    assert(dict_get(dict, key) == val);
    assert(dict_set(dict, key, val_) == DICT_OK);
    assert(dict_get(dict, key) == val_);
    dict_free(dict);
}

void
case_dict_get()
{
    struct dict *dict = dict();
    char *key = "key", *val = "val";
    assert(dict_set(dict, key, val) == DICT_OK);
    assert(dict_len(dict) == 1);
    assert(dict_get(dict, key) == val);
    assert(dict_get(dict, "not exist") == NULL);
    dict_free(dict);
}

void
case_dict_pop()
{
    struct dict *dict = dict();
    char *key = "key", *val = "val";
    assert(dict_set(dict, key, val) == DICT_OK);
    assert(dict_len(dict) == 1);
    assert(dict_pop(dict, key) == val);
    assert(dict_len(dict) == 0);
    assert(dict_pop(dict, key) == NULL);
    assert(dict_len(dict) == 0);
    dict_free(dict);
}

void
case_dict_has()
{
    struct dict *dict = dict();
    char *key = "key", *val = "val";
    assert(dict_set(dict, key, val) == DICT_OK);
    assert(!dict_has(dict, "not exist"));
    assert(dict_has(dict, key));
    dict_free(dict);
}

void
case_dict_clear()
{
    struct dict *dict = dict();
    assert(dict_set(dict, "key1", "val1") == DICT_OK);
    assert(dict_set(dict, "key2", "val2") == DICT_OK);
    assert(dict_set(dict, "key3", "val3") == DICT_OK);
    assert(dict_set(dict, "key4", "val4") == DICT_OK);
    assert(dict_len(dict) == 4);
    dict_clear(dict);
    assert(dict_len(dict) == 0);
    dict_free(dict);
}

void
case_dict_resize()
{
    struct dict *dict = dict();
    assert(dict_set(dict, "key1", "val1") == DICT_OK);
    assert(dict_set(dict, "key2", "val2") == DICT_OK);
    assert(dict_set(dict, "key3", "val3") == DICT_OK);
    assert(dict_set(dict, "key4", "val4") == DICT_OK);
    assert(dict_len(dict) == 4);
    assert(dict->idx == 0 && dict_cap(dict) == 7);
    assert(dict_set(dict, "key5", "val5") == DICT_OK);
    assert(dict_set(dict, "key6", "val6") == DICT_OK);
    assert(dict_len(dict) == 6);
    assert(dict->idx == 1 && dict_cap(dict) == 17);
    dict_free(dict);
}

void
case_dict_iter()
{
    struct dict *dict = dict();
    char *key1 = "key1";
    char *key2 = "key2";
    char *key3 = "key3";
    char *key4 = "key4";
    char *key5 = "key5";
    char *key6 = "key6";
    assert(dict_set(dict, key1, "val1") == DICT_OK);
    assert(dict_set(dict, key2, "val2") == DICT_OK);
    assert(dict_set(dict, key3, "val3") == DICT_OK);
    assert(dict_set(dict, key4, "val4") == DICT_OK);
    assert(dict_set(dict, key5, "val5") == DICT_OK);
    assert(dict_set(dict, key6, "val6") == DICT_OK);

    struct dict_iter *iter = dict_iter(dict);

    assert(dict_iter_next(iter) != NULL);
    assert(dict_iter_next(iter) != NULL);
    assert(dict_iter_next(iter) != NULL);
    assert(dict_iter_next(iter) != NULL);
    assert(dict_iter_next(iter) != NULL);
    assert(dict_iter_next(iter) != NULL);
    assert(dict_iter_next(iter) == NULL);
    dict_iter_free(iter);
    dict_free(dict);
}
