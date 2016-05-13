// cc heap_example.c heap.c

#include <assert.h>
#include <stdio.h>

#include "heap.h"

/* heap node comparator type, return negative if arg#0 < arg#1 */
int cmp(void *a, void *b) { return *(int *)a - *(int *)b; }
int main(int argc, const char *argv[]) {
    /* allocate empty heap with comparator */
    struct heap *heap = heap(cmp);
    /* push data into heap */
    int a = 4, b = 1, c = 3, d = 2, e = 5;
    assert(heap_push(heap, &a) == HEAP_OK);
    assert(heap_push(heap, &b) == HEAP_OK);
    assert(heap_push(heap, &c) == HEAP_OK);
    assert(heap_push(heap, &d) == HEAP_OK);
    assert(heap_push(heap, &e) == HEAP_OK);
    /* get current heap memory capacity (or memory allocated) */
    printf("current heap allocated memory: %zu\n", heap_cap(heap));
    printf("current heap length: %zu\n", heap_len(heap));
    /* get current smallest data */
    printf("smallest: %d\n", *(int *)heap_top(heap));
    /* pop and print all data (should be in order) */
    while (heap_len(heap) != 0) printf("%d\n", *(int *)heap_pop(heap));
    /* free heap */
    heap_free(heap);
    return 0;
}
