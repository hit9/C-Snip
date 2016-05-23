/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "event.h"

/* Get time now in milliseconds. */
static long event_time_now(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000;
}

/**
 * Event timer heap
 */

/* Create a timer heap. */
struct event_timer_heap *event_timer_heap_new(void) {
    struct event_timer_heap *heap = malloc(sizeof(struct event_timer_heap));
    if (heap != NULL) heap->len = 0;
    return heap;
}

/* Free a timer heap. */
void event_timer_heap_free(struct event_timer_heap *heap) {
    if (heap != NULL) free(heap);
}

/* Sift down the timer heap. */
void event_timer_heap_siftdown(struct event_timer_heap *heap, size_t start_idx,
                               size_t idx) {
    assert(heap != NULL && heap->timers != NULL);

    size_t parent_idx;
    struct event_timer *parent;
    struct event_timer *timer = heap->timers[idx];

    while (idx > start_idx) {
        parent_idx = (idx - 1) >> 1;
        parent = heap->timers[parent_idx];
        if (timer->fire_at < parent->fire_at) {
            heap->timers[idx] = parent;
            idx = parent_idx;
            continue;
        }
        break;
    }
    heap->timers[idx] = timer;
}

/* Sift up the timer heap. */
void event_timer_heap_siftup(struct event_timer_heap *heap, size_t idx) {
    assert(heap != NULL && heap->timers != NULL);

    size_t len = heap->len;
    size_t start_idx = idx;
    size_t child_idx = idx * 2 + 1;
    size_t right_idx;
    struct event_timer *timer = heap->timers[idx];

    while (child_idx < len) {
        right_idx = child_idx + 1;
        if (right_idx < len &&
            heap->timers[child_idx]->fire_at >=
                heap->timers[right_idx]->fire_at)
            child_idx = right_idx;
        heap->timers[idx] = heap->timers[child_idx];
        idx = child_idx;
        child_idx = idx * 2 + 1;
    }

    heap->timers[idx] = timer;
    event_timer_heap_siftdown(heap, start_idx, idx);
}

/* Push a timer into timer heap. */
int event_timer_heap_push(struct event_timer_heap *heap,
                          struct event_timer *timer) {
    assert(heap != NULL && heap->timers != NULL);

    if (heap->len >= EVENT_TIMER_ID_MAX) return EVENT_ERANGE;

    heap->timers[heap->len++] = timer;
    event_timer_heap_siftdown(heap, 0, heap->len - 1);
    return EVENT_OK;
}

/* Pop a timer from heap, NULL on empty. */
struct event_timer *event_timer_heap_pop(struct event_timer_heap *heap) {
    assert(heap != NULL && heap->timers != NULL);

    if (heap->len == 0) return NULL;

    struct event_timer *tail = heap->timers[--heap->len];
    if (heap->len == 0) return tail;
    struct event_timer *head = heap->timers[0];
    heap->timers[0] = tail;
    event_timer_heap_siftup(heap, 0);
    return head;
}

/* Get the smallest timer from heap, NULL on empty. */
struct event_timer *event_timer_heap_top(struct event_timer_heap *heap) {
    assert(heap != NULL && heap->timers != NULL);

    if (heap->len == 0) return NULL;
    return heap->timers[0];
}

/* Delete timer by id from heap. */
int event_timer_heap_del(struct event_timer_heap *heap, int id) {
    assert(heap != NULL && heap->timers != NULL);

    if (id < 0 || id >= EVENT_TIMER_ID_MAX) return EVENT_ERANGE;

    if (heap->len == 0) return EVENT_ENOTFOUND;

    int i;
    for (i = 0; i < heap->len; i++) {
        if (heap->timers[i]->id == id) {
            heap->len -= 1;
            if (heap->len > 0) {
                heap->timers[i] = heap->timers[heap->len];
                event_timer_heap_siftup(heap, i);
            }
            return EVENT_OK;
        }
    }
    return EVENT_ENOTFOUND;
}

/* Replace the top item with another. */
int event_timer_heap_replace(struct event_timer_heap *heap,
                             struct event_timer *timer) {
    assert(heap != NULL && heap->timers != NULL);

    if (heap->len == 0) return EVENT_ERANGE;
    heap->timers[0] = timer;
    event_timer_heap_siftup(heap, 0);
    return EVENT_OK;
}

/**
 * Event loop.
 */

/**
 * Get the nearest timer to fire from timer heap. O(1)
 */
struct event_timer *event_nearest_timer(struct event_loop *loop) {
    assert(loop != NULL && loop->timers != NULL && loop->timer_heap != NULL);
    return event_timer_heap_top(loop->timer_heap);
}

/**
 * Fire timed out timers from heap and update their fire_at. O(log(N)).
 */
void event_process_timers(struct event_loop *loop) {
    assert(loop != NULL && loop->timers != NULL && loop->timer_heap);

    struct event_timer *timer;

    while (1) {
        timer = event_timer_heap_top(loop->timer_heap);
        if (timer == NULL) /* no waiting timers to be processed */
            break;
        if (timer->fire_at <= event_time_now()) {
            /* fire this timeouted timer */
            if (timer->cb != NULL) (timer->cb)(loop, timer->id, timer->data);
            if (timer->id < 0) {
                continue;  // won't push back if the timer is invalid now.
            }
            /* push back the timer */
            timer->fire_at += timer->interval;
            event_timer_heap_replace(loop->timer_heap, timer);
            continue;
        }
        /* the other timers are not ready now */
        break;
    }
}
