/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "event.h"

#ifdef HAVE_KQUEUE
#include "event_kqueue.c"
#else
    #ifdef HAVE_EPOLL
    #include "event_epoll.c"
    #else
    #error "no event lib avaliable"
    #endif
#endif

/* Get time now in milliseconds. */
static long
event_time_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec + tv.tv_usec) / 1000;
}

/* Create an event loop. */
struct event_loop *
event_loop_new(int size)
{
    assert(size > 0);

    /* event numbers must be greater than RESERVED_FDS + FDSET_INCR */
    size += EVENT_FDSET_INCR + EVENT_MIN_RESERVED_FDS;

    struct event_loop *loop = malloc(sizeof(struct event_loop));

    if (loop == NULL)
        return NULL;

    loop->size = size;
    loop->events = NULL;
    loop->api = NULL;
    loop->num_timers = 0;

    int i;
    for (i = 0; i < EVENT_TIMER_ID_MAX; i++)
        loop->timers[i].id = -1;

    loop->events = malloc(sizeof(struct event) * size);

    if (loop->events == NULL) {
        free(loop);
        return NULL;
    }

    if (event_api_loop_new(loop) != EVENT_OK) {
        free(loop->events);
        free(loop);
        return NULL;
    }

    for (i = 0; i < size; i++)
        loop->events[i].mask = EVENT_NONE;
    return loop;
}

/* Free an event loop. */
void
event_loop_free(struct event_loop *loop)
{
    if (loop != NULL) {
        event_api_loop_free(loop);
        if (loop->events != NULL)
            free(loop->events);
        free(loop);
    }
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

/* Wait for events. */
int
event_wait(struct event_loop *loop)
{
    assert(loop != NULL);

    long time_now = event_time_now();
    long timeout = -1;  /* block forever */
    struct event_timer *nearest_timer = event_nearest_timer(loop);

    if (nearest_timer != NULL)
        timeout = nearest_timer-> next_fire_at - time_now;

    int result = event_api_wait(loop, timeout);
    long elapsed = event_time_now() - time_now;
    long alignment = 0;
    if (timeout >= 0 && elapsed > timeout)
        alignment = elapsed - timeout;
    event_process_timers(loop, alignment);
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

/* Add timer to event loop. (interval#ms) */
int
event_add_timer(struct event_loop *loop, long interval,
        event_timer_cb_t cb, void *data)
{
    assert(loop != NULL && loop->timers != NULL);
    assert(interval > 0);

    int id;
    struct event_timer *timer;

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
    timer->next_fire_at = event_time_now() + interval;
    timer->data = data;
    loop->num_timers += 1;
    return EVENT_OK;
}

/* Delete timer from event loop. */
int
event_del_timer(struct event_loop *loop, int id)
{
    assert(loop != NULL && loop->timers != NULL);

    if (id < 0 || id >= EVENT_TIMER_ID_MAX)
        return EVENT_ERANGE;
    struct event_timer *timer = &loop->timers[id];
    if (timer->id < 0)
        return EVENT_ENOTFOUND;
    timer->id = -1;
    loop->num_timers -= 1;
    return EVENT_OK;
}

/* Get nearest timer, this will do an O(EVENT_TIMER_ID_MAX) loop to
 * search timer with the smallest `next_fire_at`, `NULL` on not found
 * (that means `event_wait` will block forever for a file event to fire). */
struct event_timer *
event_nearest_timer(struct event_loop *loop)
{
    assert(loop != NULL && loop->timers != NULL);

    int i, j;
    struct event_timer *timer, *nearest = NULL;

    for (i = 0, j = 0; i < EVENT_TIMER_ID_MAX && j < loop->num_timers; i++) {
        timer = &loop->timers[i];

        if (timer->id >= 0) {
            if (nearest == NULL ||
                    nearest->next_fire_at > timer->next_fire_at)
                nearest = timer;
            j++;
        }
    }
    return nearest;
}

/* Fire timed out timers and update each of them `next_fire_at` with
 * `interval`. */
void
event_process_timers(struct event_loop *loop, long alignment)
{
    assert(loop != NULL && loop->timers != NULL);
    assert(alignment >= 0);

    int i, j;
    struct event_timer *timer;
    long time_now = event_time_now();

    for (i = 0, j = 0; i < EVENT_TIMER_ID_MAX && j < loop->num_timers; i++) {
        timer = &loop->timers[i];
        if (timer->id >= 0) {
            timer->next_fire_at += alignment;
            while (timer->next_fire_at <= time_now) {
                timer->next_fire_at += timer->interval;
                if (timer->cb != NULL)
                    (timer->cb)(loop, timer->id, timer->data);
            }
            j += 1;
        }
    }
}
