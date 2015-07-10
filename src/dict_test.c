/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>
#include "test.h"
#include "errors.h"
#include "dict.h"

void
case_dict_set()
{
    struct dict *dict = dict();
    char *key = "key", *val = "val";
    size_t len = strlen(key);
    assert(dict_set(dict, key, len, val) == ERR_OK);
    assert(dict_get(dict, key, len) == val);
    dict_free(dict);
}
