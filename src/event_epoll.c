/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "event.h"

/* Create an event loop. */
struct event_loop *
event_loop_new(int nevents)
{
    assert(nevents >= 0);

    struct event_loop *loop = malloc(sizeof(struct event_loop));

    if (loop == NULL)
        return NULL;

    int ep = epoll_create(nevents);

    if (ep < 0) {
        free(loop);
        return NULL;
    }

    loop->ep = ep;
    loop->nevents = nevents;
    loop->events = malloc(sizeof(epoll_event) * nevents);

    if (loop->events == NULL) {
        close(ep);
        free(loop);
        return NULL;
    }
    return loop;
}

/* Free an event loop. */
void
event_loop_free(struct event_loop *loop)
{
    if (loop != NULL) {
        if (loop->ep > 0)
            close(loop->ep);
        if (loop->events != NULL)
            free(loop->events);
        free(loop);
    }
}

/* Add an event to event loop. */
int
event_loop_add(struct event_loop *loop, int fd, int op,
        event_cb_t cb, void *data)
{
    assert(loop != NULL);
    assert(cb != NULL);

    struct epoll_event ev;
    struct event_data ed;

    ed.op = op;
    ed.cb = cb;
    ed.data = data;

    ev.data.fd = fd;
    ev.data.ptr = &ed;
    ev.events = 0;

    if (op & EVENT_READABLE) ev.events |= EPOLLIN;
    if (op & EVENT_WRITABLE) ev.events |= EPOLLOUT;
    if (op & EVENT_ET) ev.events |= EPOLLET;

    if (epoll_ctl(loop->ep, EPOLL_CTL_ADD, fd, &ev) < 0)
        return EVENT_EFAILED;
    return EVENT_OK;
}

/* Delete an event to event loop. */
