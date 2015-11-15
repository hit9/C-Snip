// cc strings_example.c strings.c
#include <stdio.h>
#include "strings.h"

void
example_search()
{
    /* search string via Boyer Moore algorithm */
    char *s = "this is a simple example";
    char *sub = "mp";
    size_t first_idx = strings_search(s, sub, 0);
    size_t second_idx = strings_search(s, sub, first_idx + 1);
    printf("'%s' is seen in '%s' at index %zu\n", sub, s, first_idx);
    printf("'%s' is seen in '%s' again at index %zu\n", sub, s, second_idx);
}

void
example_rand()
{
    /* get some random strings (length 20) */
    char s[20];
    printf("random string with length 20: %s\n", strings_rand(s, 20));
    printf("random string with length 20: %s\n", strings_rand(s, 20));
    printf("random string with length 20: %s\n", strings_rand(s, 20));
}

void
example_replace()
{
    /* replace string example */
    char *src = "this is a simple example";
    char *sub = "mp";
    char *rep = "**";
    char dst[100] = {0};
    strings_replace(dst, src, sub, rep);
    printf("replace '%s' in '%s' with '%s': '%s'\n", sub, src, rep, dst);
}

int main(int argc, const char *argv[])
{
    example_search();
    example_rand();
    example_replace();
    return 0;
}
