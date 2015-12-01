// cc dict_example.c dict.c md5.c

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dict.h"

int main(int argc, const char *argv[])
{
    /* allocate a new dict */
    struct dict *dict = dict();
    /* set key and values to dict */
    char *key1 = "key1";
    char *key2 = "key2";
    char *val1 = "val1";
    char *val2 = "val2";
    assert(dict_set(dict, key1, val1) == DICT_OK);
    assert(dict_set(dict, key2, val2) == DICT_OK);
    /* get dict length */
    assert(dict_len(dict) == 2);
    /* get data by key */
    assert(dict_get(dict, key1) == val1);
    assert(dict_get(dict, key2) == val2);
    /* iterate dict */
    struct dict_iter *iter = dict_iter(dict);
    struct dict_node *node = NULL;
    while ((node = dict_iter_next(iter)) != NULL) {
        printf("%s => %s\n", node->key, (char *)node->val);
    }
    /* free dict iterator */
    dict_iter_free(iter);
    /* free the dict */
    dict_free(dict);
    return 0;
}
