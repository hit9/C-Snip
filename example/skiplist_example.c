// cc skiplist_example.c skiplist.c

#include <assert.h>
#include <stdio.h>
#include "skiplist.h"

int main(int argc, const char *argv[]) {
    /* allocate a new empty skiplist (using default score comparator) */
    struct skiplist *skiplist = skiplist(NULL);
    /* push data into skiplist */
    unsigned long a = 4, b = 2, c = 3, d = 7, e = 5, f = 6, g = 9, h = 8, i = 1;
    assert(skiplist_push(skiplist, a, "a") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, b, "b") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, c, "c") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, d, "d") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, e, "e") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, f, "f") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, g, "g") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, i, "i") == SKIPLIST_OK);
    assert(skiplist_push(skiplist, h, "h") == SKIPLIST_OK);
    /* get data by node */
    printf("score: %lu => data: %s\n", a, (char *)skiplist_get(skiplist, a));
    printf("score: %lu => data: %s\n", b, (char *)skiplist_get(skiplist, b));
    printf("score: %lu => data: %s\n", c, (char *)skiplist_get(skiplist, c));
    printf("score: %lu => data: %s\n", d, (char *)skiplist_get(skiplist, d));
    printf("score: %lu => data: %s\n", e, (char *)skiplist_get(skiplist, e));
    printf("score: %lu => data: %s\n", f, (char *)skiplist_get(skiplist, f));
    printf("score: %lu => data: %s\n", g, (char *)skiplist_get(skiplist, g));
    printf("score: %lu => data: %s\n", h, (char *)skiplist_get(skiplist, h));
    printf("score: %lu => data: %s\n", i, (char *)skiplist_get(skiplist, i));
    /* print current skiplist */
    skiplist_print(skiplist);
    /* iterate the skiplist */
    struct skiplist_node *node;
    skiplist_each(skiplist, node) { printf("%lu ", node->score); }
    printf("\n");
    /* get the first and last node */
    struct skiplist_node *first = skiplist_first(skiplist);
    struct skiplist_node *last = skiplist_last(skiplist);
    printf("first node => score: %ld, data: '%s'\n", first->score,
           (char *)first->data);
    printf("last node  => score: %ld, data: '%s'\n", last->score,
           (char *)last->data);
    /* pop the first and last node */
    printf("pop first node, data: '%s'\n", (char *)skiplist_popfirst(skiplist));
    printf("pop last node, data: '%s'\n", (char *)skiplist_poplast(skiplist));
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
