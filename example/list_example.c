// cc list_example.c list.c

#include <assert.h>
#include <stdio.h>
#include "list.h"

int main(int argc, const char *argv[]) {
    /* allocate a empty list */
    struct list *list = list();
    /* push data to the list (on the right)*/
    assert(list_push(list, "a") == LIST_OK);
    assert(list_push(list, "b") == LIST_OK);
    assert(list_push(list, "c") == LIST_OK);
    assert(list_push(list, "d") == LIST_OK);
    /* get list current length */
    assert(list_len(list) == 4);
    /* pop a node from list (on the left) */
    assert(list_pop(list) != NULL);
    /* iterate the list and print the nodes */
    struct list_node *node;
    list_each(list, node) { printf("%s ", (char *)node->data); }
    /* free the list */
    list_free(list);
    return 0;
}
