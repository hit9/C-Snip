/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>
#include "bench.h"
#include "heap.h"

int heap_bench_cmp(void *a, void *b) { return *(int *)a - *(int *)b; }

void case_heap_push(struct bench_ctx *ctx) {
    struct heap *heap = heap(&heap_bench_cmp);
    int i;
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        heap_push(heap, &i);
    }
    bench_ctx_reset_end_at(ctx);
    heap_free(heap);
}

void case_heap_pop(struct bench_ctx *ctx) {
    struct heap *heap = heap(&heap_bench_cmp);
    int i;
    for (i = 0; i < ctx->n; i++) {
        heap_push(heap, &i);
    }
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        heap_pop(heap);
    }
    bench_ctx_reset_end_at(ctx);
    heap_free(heap);
}

void case_heap_top(struct bench_ctx *ctx) {
    struct heap *heap = heap(&heap_bench_cmp);
    int i;
    for (i = 0; i < ctx->n; i++) {
        heap_push(heap, &i);
    }
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        heap_top(heap);
    }
    bench_ctx_reset_end_at(ctx);
    heap_free(heap);
}
