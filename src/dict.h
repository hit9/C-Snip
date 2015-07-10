/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic sized list-based hashtable implementation.
 */

#ifndef _CW_DICT_H
#define _CW_DICT_H 1

#include <stdint.h>
#include "errors.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define DICT_LOAD_LIMIT     0.75  /* load factor */

struct dict_node {
    char *key;                /* key string address */
    size_t len;               /* key string length */
    void *val;                /* value data */
    struct dict_node *next;   /* next node */
};

struct dict {
    size_t idx;                /* index in table sizes */
    size_t size;               /* dict size */
    struct dict_node **table;  /* node table */
};

static size_t dict_table_sizes[] = {
    7,
    17,
    37,
    79,
    163,
    331,
    673,
    1361,
    2729,
    5471,
    10949,
    21911,
    43853,
    87719,
    175447,
    350899,
    701819,
    1403641,
    2807303,
    5614657,
    11229331,
    44917381,
    89834777,
    179669557,
    359339171,
    718678369,
    1437356741,
    2147483647,
};

static size_t dict_idx_max = sizeof(dict_table_sizes)/\
                             sizeof(dict_table_sizes[0])-1;  /* 28 */

#if defined(__cplusplus)
}
#endif

#endif
