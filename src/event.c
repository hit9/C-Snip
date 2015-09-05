/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "event.h"

#ifdef HAVE_EVPORT
#include "event_evport.c"
#else
    #ifdef HAVE_EPOLL
    #include "event_epoll.c"
    #else
        #ifdef HAVE_KQUEUE
        #include "event_kqueue.c"
        #else
        #include "event_select.c"
        #endif
    #endif
#endif

/* Create an event loop. */
struct event_loop *
event_loop_new(int size)
{
    assert(size > 0);

    struct event_loop *loop = malloc(sizeof(struct event_loop));

    if (loop == NULL)
        return NULL;

    loop->size = size;
    loop->events = NULL;
    loop->api = NULL;

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

    int i;

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

    struct event *ev = loop->events[fd];
    ev->mask |= mask;

    if (mask & EVENT_READABLE) ev->rcb = cb;
    if (mask & EVENT_WRITABLE) ev->wcb = cb;
    if (mask & EVENT_ERROR) ev->ecb = cb;

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

    struct event *ev = loop->events[fd];

    if (ev->mask == EVENT_NONE)
        return EVENT_OK;

    int err = event_api_del(eventLoop, fd, mask);

    if (err != EVENT_OK)
        return err;

    ev->mask = ev->mask & (~mask);
    return EVENT_OK;
}

/* Wait for events. */
int
event_wait(struct event_loop *loop, int timeout)
{
    return event_api_wait(loop, timeout);
}

/* Start event loop */
int
event_loop_start(struct event_loop *loop, int timeout)
{
    int err;

    for(;;)
        if ((err = event_wait(loop, timeout)) != EVENT_OK)
            return err;

    return EVENT_OK;
}
