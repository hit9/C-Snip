/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "heap.h"

/* Create an empty heap. */
struct heap *
heap_new(heap_cmp_t cmp)
{
    struct heap *heap = malloc(sizeof(struct heap));

    if (heap != NULL) {
        heap->cap = 0;
        heap->len = 0;
        heap->cmp = cmp;
        heap->data = NULL;
    }
    return heap;
}

/* Free heap. */
void
heap_free(struct heap *heap)
{
    if (heap != NULL) {
        if (heap->data != NULL)
            free(heap->data);
        free(heap);
    }
}

/* Clear a heap. */
void
heap_clear(struct heap *heap)
{
    assert(heap != NULL);
    heap->len = 0;
}

/* Get heap length. */
size_t
heap_len(struct heap *heap)
{
    assert(heap != NULL);
    return heap->len;
}

/* Get heap cap. */
size_t
heap_cap(struct heap *heap)
{
    assert(heap != NULL);
    return heap->cap;
}

/* Grow a heap's memory capacity to given cap. */
int
heap_grow(struct heap *heap, size_t cap)
{
    assert(heap != NULL);

    if (cap > HEAP_CAP_MAX)
        return HEAP_ENOMEM;

    if (cap <= heap->cap)
        return HEAP_OK;

    size_t unit = heap->cap;

    if (unit > HEAP_UNIT_MAX)
        unit = HEAP_UNIT_MAX;

    if (unit < HEAP_UNIT_MIN)
        unit = HEAP_UNIT_MIN;

    size_t new_cap = heap->cap + unit;
    while (new_cap < cap)
        new_cap += unit;

    void **data = realloc(heap->data, new_cap * sizeof(void *));
    if (data == NULL)
        return HEAP_ENOMEM;

    heap->data = data;
    heap->cap = new_cap;

    if (heap->len > new_cap)
        heap->len = new_cap;
    return HEAP_OK;
}

/* Push data to heap. */
int
heap_push(struct heap *heap, void *data)
{
    assert(heap != NULL);

    if (heap->len <= heap->cap &&
            heap_grow(heap, heap->len + 1) != HEAP_OK)
        return HEAP_ENOMEM;

    assert(heap->data != NULL);
    heap->data[heap->len++] = data;
    heap_siftdown(heap, 0, heap->len - 1);
    return HEAP_OK;
}

/* Pop data from heap, NULL on empty. */
void *
heap_pop(struct heap *heap)
{
    assert(heap != NULL);

    if (heap->len == 0)
        return NULL;

    assert(heap->data != NULL && heap->len >= 1);

    void *tail = heap->data[--heap->len];

    if (heap->len == 0)
        return tail;
    void *head = heap->data[0];
    heap->data[0] = tail;
    heap_siftup(heap, 0);
    return head;
}

/* Push data to heap and pop the top, this runs more efficiently
 * than `heap_push` followed by a separate call to `heap_pop`. */
void *
heap_pushpop(struct heap *heap, void *data)
{
    assert(heap != NULL);

    if (heap->len == 0)
        return data;

    assert(heap->data != NULL);

    void *head = heap->data[0];

    if ((heap->cmp)(head, data)) {
        heap->data[0] = data;
        data = head;
        heap_siftup(heap, 0);
    }
    return data;
}

/* Get the smallest data from heap, NULL on empty. */
void *
heap_top(struct heap *heap)
{
    assert(heap != NULL);

    if (heap->len == 0)
        return NULL;

    assert(heap->data != NULL && heap->len >= 1);
    return heap->data[0];
}

/* Sift down the heap. */
void
heap_siftdown(struct heap *heap, size_t start_idx, size_t idx)
{
    assert(heap != NULL && heap->data != NULL);

    size_t parent_idx;
    void *parent_data;
    void *data = heap->data[idx];

    while (idx > start_idx) {
        parent_idx = (idx - 1) >> 1;
        parent_data = heap->data[parent_idx];

        if ((heap->cmp)(data, parent_data)) {
            heap->data[idx] = parent_data;
            idx = parent_idx;
            continue;
        }
        break;
    }

    heap->data[idx] = data;
}

/* Sift up the heap. */
void
heap_siftup(struct heap *heap, size_t idx)
{
    assert(heap != NULL && heap->data != NULL);

    void *data = heap->data[idx];

    size_t len = heap->len;
    size_t start_idx = idx;
    size_t child_idx = idx * 2 + 1;
    size_t right_idx;
    void *child_data;
    void *right_data;

    while (child_idx < len) {
        right_idx = child_idx + 1;

        if (right_idx < len &&
                !(heap->cmp)(heap->data[child_idx], heap->data[right_idx]))
            child_idx = right_idx;
        heap->data[idx] = heap->data[child_idx];
        idx = child_idx;
        child_idx = idx * 2 + 1;
    }

    heap->data[idx] = data;
    heap_siftdown(heap, start_idx, idx);
}
