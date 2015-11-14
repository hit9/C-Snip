/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>
#include "test.h"
#include "strings.h"

void
case_strings_search()
{
    char s1[] = "this is a simple example";
    assert(strings_search(s1, "this", 0) == 0);
    assert(strings_search(s1, "is", 0) == 2);
    assert(strings_search(s1, "is", 3) == 5);
    assert(strings_search(s1, "mp", 0) == 12);
    assert(strings_search(s1, "mp", 13) == 20);
    assert(strings_search(s1, "not exist", 0) == strlen(s1));

    char s2[] = "这是中文是的";
    assert(strings_search(s2, "这是", 0) == 0);
    assert(strings_search(s2, "中文", 0) == 6);
    assert(strings_search(s2, "是", 0) == 3);
    assert(strings_search(s2, "是", 6) == 12);
}

void
case_strings_rand()
{
    /* we are going to assert n times random strings (with length 16)
     * are not the same with each other */
    int n = 100;
    char strings[n][17]; /* because 2d array are continuously on
                            memory, so we use 16+1 */
    char *s;
    int i, j;

    for (i = 0; i < n; i++) {
        strings_rand(strings[i], 16);
        for (j = 0; j < i; j++)
            assert(strcmp(strings[i], strings[j]) != 0);
    }
}
