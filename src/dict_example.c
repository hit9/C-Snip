// cc dict_example.c dict.c

#include <assert.h>
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
    assert(dict_set(dict, key1, strlen(key1), val1) == DICT_OK);
    assert(dict_set(dict, key2, strlen(key2), val2) == DICT_OK);
    /* get dict length */
    assert(dict_len(dict) == 2);
    /* free the dict */
    dict_free(dict);
    return 0;
}
