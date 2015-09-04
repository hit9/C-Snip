/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>
#include "test.h"
#include "utils.h"

void
case_utils_bm_search()
{
    char s1[] = "this is a simple example";
    assert(bm_search(s1, "this", 0) == 0);
    assert(bm_search(s1, "is", 0) == 2);
    assert(bm_search(s1, "is", 3) == 5);
    assert(bm_search(s1, "mp", 0) == 12);
    assert(bm_search(s1, "mp", 13) == 20);
    assert(bm_search(s1, "not exist", 0) == strlen(s1));

    char s2[] = "这是中文是的";
    assert(bm_search(s2, "这是", 0) == 0);
    assert(bm_search(s2, "中文", 0) == 6);
    assert(bm_search(s2, "是", 0) == 3);
    assert(bm_search(s2, "是", 6) == 12);
}
