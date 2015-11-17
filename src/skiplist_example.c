// cc skiplist_example.c skiplist.c

#include <assert.h>
#include <stdio.h>
#include "skiplist.h"

int
cmp(unsigned long score1, unsigned long score2)
{
    return score1 - score2;
}

int main(int argc, const char *argv[])
{
    /* allocate a new empty skiplist */
    struct skiplist *skiplist = skiplist(&cmp);
    /* push data into skiplist */
    unsigned long a = 4, b = 2, c = 3, d = 7, e = 5, f = 6,
                  g = 9, h = 8, i = 1;
    assert(skiplist_push(skiplist, a, "a") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, b, "b") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, c, "c") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, d, "d") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, e, "e") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, f, "f") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, g, "g") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, i, "i") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, h, "h") == SKIPLIST_OK);
    /* print current skiplist */
    skiplist_print(skiplist);
    /* get the first and last node */
    struct skiplist_node *first = skiplist_first(skiplist);
    struct skiplist_node *last = skiplist_last(skiplist);
    printf("first node: {score: %ld, data: '%s'}\n", first->score, (char *)first->data);
    printf("last node: {score: %ld, data: '%s'}\n", last->score, (char *)last->data);
    /* pop the first and last node */
    printf("pop first node, data: '%s'\n", (char *)skiplist_popfirst(skiplist));
    printf("pop last node, data: '%s'\n", (char *)skiplist_poplast(skiplist));
    skiplist_print(skiplist);
    /* print current skiplist length and height */
    printf("skiplist height: %d\n", skiplist_height(skiplist));
    printf("skiplist len: %zu\n", skiplist_len(skiplist));
    /* clear the skiplist */
    skiplist_clear(skiplist);
    printf("skiplist height after clear: %d\n", skiplist_height(skiplist));
    printf("skiplist len after clear: %zu\n", skiplist_len(skiplist));
    skiplist_print(skiplist);
    return 0;
}
