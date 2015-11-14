// cc strings_example.c strings.c
#include <stdio.h>
#include "strings.h"

int main(int argc, const char *argv[])
{
    /* search string via Boyer Moore algorithm */
    char *s = "this is a simple example";
    char *sub = "mp";
    size_t first_idx = strings_search(s, sub, 0);
    size_t second_idx = strings_search(s, sub, first_idx + 1);
    printf("'%s' is seen in '%s' at index %zu\n", sub, s, first_idx);
    printf("'%s' is seen in '%s' again at index %zu\n", sub, s, second_idx);
    /* get some random strings (length 20) */
    char s1[20];
    printf("random string with length 20: %s\n", strings_rand(s1, 20));
    printf("random string with length 20: %s\n", strings_rand(s1, 20));
    printf("random string with length 20: %s\n", strings_rand(s1, 20));
    return 0;
}
