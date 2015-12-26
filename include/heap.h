/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Array based binary heap (or priority queue) implementation.
 * deps: None.
 */

#ifndef _CW_HEAP_H
#define _CW_HEAP_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define HEAP_CAP_MAX    16*1024*1024 /* max memory capacity: 16mb */
#define HEAP_UNIT_MIN   1            /* min heap realloc unit: 1 */
#define HEAP_UNIT_MAX   1024         /* max heap realloc unit: 1kb */

#define heap(cmp)       heap_new(cmp)

/* heap node comparator type, return negative if arg#0 < arg#1 */
typedef int (*heap_cmp_t)(void *, void *);

enum {
    HEAP_OK = 0,             /* operation is ok */
    HEAP_ENOMEM = 1,         /* no memory error */
};

struct heap {
    void **data;             /* heap array data */
    size_t cap;              /* heap capacity */
    size_t len;              /* heap length */
    heap_cmp_t cmp;          /* node data comparator */
};

struct heap *heap_new(heap_cmp_t cmp);
void heap_free(struct heap *heap);
void heap_clear(struct heap *heap);  /* O(1). */
size_t heap_len(struct heap *heap);  /* O(1) */
size_t heap_cap(struct heap *heap);  /* O(1) */
int heap_grow(struct heap *heap, size_t cap);
void *heap_pop(struct heap *heap);   /* O(logN) */
int heap_push(struct heap *heap, void *data);  /* O(logN) */
void *heap_pushpop(struct heap *heap, void *data);  /* O(logN) */
void *heap_top(struct heap *heap);  /* O(1) */
void *heap_del(struct heap *heap, size_t idx); /* O(N) */
void heap_siftdown(struct heap *heap, size_t start_idx, size_t idx);  /* O(logN) */
void heap_siftup(struct heap *heap, size_t idx);  /* O(logN) */

#if defined(__cplusplus)
}
#endif

#endif
