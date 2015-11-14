/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "test.h"
#include "heap.h"


bool
heap_cmp(void *a, void *b)
{
    return *(int *)a < *(int *)b;
}

void
case_heap_clear()
{
    struct heap *heap = heap(heap_cmp);
    int a = 1;
    assert(heap_push(heap, (void *)&a) == HEAP_OK);
    assert(heap_len(heap) == 1);
    assert(heap_cap(heap) == 1);
    heap_clear(heap);
    assert(heap_len(heap) == 0);
    heap_free(heap);
}

void
case_heap_len()
{
    struct heap *heap = heap(heap_cmp);
    assert(heap_len(heap) == 0);
    int a = 1, b = 2, c = 3;
    assert(heap_push(heap, (void *)&a) == HEAP_OK);
    assert(heap_push(heap, (void *)&b) == HEAP_OK);
    assert(heap_push(heap, (void *)&c) == HEAP_OK);
    assert(heap_len(heap) == 3);
    heap_free(heap);
}

void
case_heap_cap()
{
    struct heap *heap = heap(heap_cmp);
    assert(heap_cap(heap) == 0);
    int a = 1, b = 2, c = 3;
    assert(heap_push(heap, (void *)&a) == HEAP_OK);
    assert(heap_cap(heap) == 1);
    assert(heap_push(heap, (void *)&b) == HEAP_OK);
    assert(heap_cap(heap) == 2);
    assert(heap_push(heap, (void *)&c) == HEAP_OK);
    assert(heap_cap(heap) == 4);
    heap_free(heap);
}

void
case_heap_push()
{
    struct heap *heap = heap(heap_cmp);
    int a = 3, b = 1, c = 2;
    assert(heap_push(heap, (void *)&a) == HEAP_OK);
    assert(heap_push(heap, (void *)&b) == HEAP_OK);
    assert(heap_push(heap, (void *)&c) == HEAP_OK);
    assert(heap_len(heap) == 3);
    assert(*(int *)heap_pop(heap) == 1);
    assert(*(int *)heap_pop(heap) == 2);
    assert(*(int *)heap_pop(heap) == 3);
    heap_free(heap);
}

void
case_heap_pop()
{
    struct heap *heap = heap(heap_cmp);
    int a = 3, b = 1, c = 2, d = 4;
    assert(heap_push(heap, (void *)&a) == HEAP_OK);
    assert(heap_push(heap, (void *)&b) == HEAP_OK);
    assert(heap_push(heap, (void *)&c) == HEAP_OK);
    assert(heap_push(heap, (void *)&d) == HEAP_OK);
    assert(heap_len(heap) == 4);
    assert(*(int *)heap_pop(heap) == 1);
    assert(*(int *)heap_pop(heap) == 2);
    assert(*(int *)heap_pop(heap) == 3);
    assert(*(int *)heap_pop(heap) == 4);
    assert(heap_len(heap) == 0);
    heap_free(heap);
}

void
case_heap_top()
{
    struct heap *heap = heap(heap_cmp);
    int a = 3, b = 2, c = 4, d = 1;
    assert(heap_push(heap, (void *)&a) == HEAP_OK);
    assert(*(int *)(heap_top(heap)) == 3);
    assert(heap_push(heap, (void *)&b) == HEAP_OK);
    assert(*(int *)(heap_top(heap)) == 2);
    assert(heap_push(heap, (void *)&c) == HEAP_OK);
    assert(*(int *)(heap_top(heap)) == 2);
    assert(heap_push(heap, (void *)&d) == HEAP_OK);
    assert(*(int *)(heap_top(heap)) == 1);
    heap_free(heap);
}

void
case_heap_pushpop()
{
    struct heap *heap = heap(heap_cmp);
    int a = 3, b = 2, c = 4;
    assert(*(int *)heap_pushpop(heap, (void *)&a) == 3);
    assert(heap_push(heap, (void *)&b) == HEAP_OK);
    assert(heap_push(heap, (void *)&c) == HEAP_OK);
    assert(*(int *)heap_pushpop(heap, (void *)&a) == 2);
    heap_free(heap);
}
