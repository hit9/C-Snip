/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "event.h"

#include "event_timer.c"
#ifdef HAVE_KQUEUE
#include "event_kqueue.c"
#else
    #ifdef HAVE_EPOLL
    #include "event_epoll.c"
    #else
    #error "no event lib avaliable"
    #endif
#endif

/* Create an event loop. */
struct event_loop *
event_loop_new(int size)
{
    assert(size >= 0);

    /* event numbers must be greater than RESERVED_FDS + FDSET_INCR */
    size += EVENT_FDSET_INCR + EVENT_MIN_RESERVED_FDS;

    struct event_loop *loop = malloc(sizeof(struct event_loop));

    if (loop == NULL)
        return NULL;

    loop->size = size;
    loop->events = NULL;
    loop->api = NULL;
    loop->num_timers = 0;

    /* events */
    loop->events = malloc(sizeof(struct event) * size);
    if (loop->events == NULL) {
        free(loop);
        return NULL;
    }

    /* event api */
    if (event_api_loop_new(loop) != EVENT_OK) {
        free(loop->events);
        free(loop);
        return NULL;
    }

    /* timer heap */
    loop->timer_heap = event_timer_heap_new();
    if (loop->timer_heap == NULL) {
        event_api_loop_free(loop);
        free(loop->events);
        free(loop);
        return NULL;
    }

    /* init all timers id to -1 */
    int i;
    for (i = 0; i < EVENT_TIMER_ID_MAX; i++)
        loop->timers[i].id = -1;

    /* init all events mask to NONE */
    for (i = 0; i < size; i++)
        loop->events[i].mask = EVENT_NONE;
    return loop;
}

/* Free an event loop. */
void
event_loop_free(struct event_loop *loop)
{
    if (loop != NULL) {
        event_timer_heap_free(loop->timer_heap);
        event_api_loop_free(loop);
        if (loop->events != NULL)
            free(loop->events);
        free(loop);
    }
}

/* Wait for events. */
int
event_wait(struct event_loop *loop)
{
    assert(loop != NULL);

    long time_now = event_time_now();
    long timeout = -1;  /* block forever */
    struct event_timer *nearest_timer = event_nearest_timer(loop);

    if (nearest_timer != NULL)
        timeout = nearest_timer->fire_at - time_now;

    int result = event_api_wait(loop, timeout);
    event_process_timers(loop);
    return result;
}

/* Start event loop */
int
event_loop_start(struct event_loop *loop)
{
    assert(loop != NULL);

    loop->state = EVENT_LOOP_RUNNING;

    int err;

    while(loop->state != EVENT_LOOP_STOPPED)
        if ((err = event_wait(loop)) != EVENT_OK)
            return err;

    return EVENT_OK;
}

/* Stop event loop */
void
event_loop_stop(struct event_loop *loop)
{
    assert(loop != NULL);
    loop->state = EVENT_LOOP_STOPPED;
}

/* Add an event to event loop (mod if the fd already in set). */
int
event_add(struct event_loop *loop, int fd, int mask,
        event_cb_t cb, void *data)
{
    assert(loop != NULL);
    assert(loop->api != NULL);
    assert(cb != NULL);

    if (fd > loop->size)
        return EVENT_ERANGE;

    int err = event_api_add(loop, fd, mask);

    if (err != EVENT_OK)
        return err;

    struct event *ev = &loop->events[fd];
    ev->mask |= mask;

    if (mask & EVENT_ERROR) ev->ecb = cb;
    if (mask & EVENT_READABLE) ev->rcb = cb;
    if (mask & EVENT_WRITABLE) ev->wcb = cb;

    ev->data = data;
    return EVENT_OK;
}

/* Delete an event from loop. */
int
event_del(struct event_loop *loop, int fd, int mask)
{
    assert(loop != NULL);

    if (fd > loop->size)
        return EVENT_ERANGE;

    struct event *ev = &loop->events[fd];

    if (ev->mask == EVENT_NONE)
        return EVENT_OK;

    int err = event_api_del(loop, fd, mask);

    if (err != EVENT_OK)
        return err;

    ev->mask = ev->mask & (~mask);
    return EVENT_OK;
}

/* Add timer to event loop. (interval#ms) */
int
event_add_timer(struct event_loop *loop, long interval,
        event_timer_cb_t cb, void *data)
{
    assert(loop != NULL && loop->timers != NULL && loop->timer_heap != NULL);
    assert(interval > 0);

    int id;
    struct event_timer *timer;

    /* find available id */
    for (id = 0; id < EVENT_TIMER_ID_MAX; id++) {
         timer = &loop->timers[id];
         if (timer->id < 0)
             break;
    }

    if (id >= EVENT_TIMER_ID_MAX)
        return EVENT_ERANGE;

    timer->id = id;
    timer->cb = cb;
    timer->interval = interval;
    timer->fire_at = event_time_now() + interval;
    timer->data = data;
    loop->num_timers += 1;
    /* push to heap */
    event_timer_heap_push(loop->timer_heap, timer);
    return EVENT_OK;
}

/* Delete timer from event loop. */
int
event_del_timer(struct event_loop *loop, int id)
{
    assert(loop != NULL && loop->timers != NULL && loop->timer_heap != NULL);

    if (id < 0 || id >= EVENT_TIMER_ID_MAX)
        return EVENT_ERANGE;

    struct event_timer *timer = &loop->timers[id];

    if (timer->id < 0)
        return EVENT_ENOTFOUND;

    timer->id = -1;
    loop->num_timers -= 1;
    return event_timer_heap_del(loop->timer_heap, id);
}
