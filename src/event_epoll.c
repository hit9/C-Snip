/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "event.h"

struct event_api {
    int ep;                      /* epoll descriptor */
    struct epoll_event *events;  /* struct epoll_events[], with size `loop->size`*/
};

static int
event_api_loop_new(struct event_loop *loop)
{
    assert(loop != NULL);
    assert(loop->size > 0);
    asseryt(loop->api == NULL);

    struct event_api *api = malloc(sizeof(struct event_api));

    if (api == NULL)
        return EVENT_ENOMEM;

    api->ep = epoll_create(loop->size);

    if (api->ep < 0) {
        free(api);
        return EVENT_EFAILED;
    }

    api->events = malloc(sizeof(struct epoll_event) * loop->size);

    if (api->events == NULL) {
        close(ep);
        free(api);
        return EVENT_ENOMEM;
    }

    loop->api = api;
    return EVENT_OK;
}

void
event_api_loop_free(struct event_loop *loop)
{
    assert(loop != NULL);

    if (loop->api != NULL) {
        if (loop->api->ep > 0)
            close(loop->api->ep);
        if (loop->api->events != NULL)
            free(loop->api->events);
        free(loop->api);
    }
}

int
event_api_add(struct event_loop *loop, int fd, int mask)
{
    assert(loop != NULL);
    assert(loop->events != NULL);
    assert(loop->api != NULL);

    struct epoll_event ev;

    int op = loop->events[fd].mask == EVENT_NONE ?
        EPOLL_CTL_ADD : EPOLL_CTL_MOD;

    ev.events = 0;
    ev.data.fd = fd;
    ev.data.u64 = 0; /* avoid valgrind warning */

    mask |= loop->events[fd].mask; /* merge old events */

    if (mask & EVENT_READABLE) ev.events |= EPOLLIN;
    if (mask & EVENT_WRITABLE) ev.events |= EPOLLOUT;
    if (mask & EVENT_ET) ev.events |= EPOLLET;

    if (epoll_ctl(loop->api->ep, op, fd, &ev) < 0)
        return EVENT_EFAILED;
    return EVENT_OK;
}

int
event_api_del(struct event_loop *loop, int fd, int delmask)
{
    assert(loop != NULL);
    assert(loop->events != NULL);
    assert(loop->api != NULL);

    struct epoll_event ev;
    int mask = loop->events[fd].mask & (~delmask);

    ev.events = 0;

    if (mask & EVENT_READABLE) ev.events |= EPOLLIN;
    if (mask & EVENT_WRITABLE) ev.events |= EPOLLOUT;
    if (mask & EVENT_ET) ev.events |= EPOLLET;

    ev.data.u64 = 0; /* avoid valgrind warning */
    ev.data.fd = fd;

    if (mask != EVENT_NONE) {
        epoll_ctl(loop->api->ep, EPOLL_CTL_MOD, fd, &ev);
    } else {
        /* Note: kernel < 2.6.9 requires a non null event pointer even for
         * EPOLL_CTL_DEL. */
        epoll_ctl(loop->api->ep, EPOLL_CTL_DEL, fd, &ev);
    }
}
