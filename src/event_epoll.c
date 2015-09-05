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
    assert(loop->api == NULL);

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
        close(api->ep);
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
    if (mask & EVENT_ERROR) ev.events |= EPOLLERR;

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
    if (mask & EVENT_ERROR) ev.events |= EPOLLERR;

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

int
event_api_wait(struct event_loop *loop, int timeout)
{
    assert(loop != NULL);
    assert(loop->events != NULL);

    struct event_api *api = loop->api;

    assert(api != NULL);
    assert(api->ep >= 0);
    assert(api->events != NULL);

    int i;
    int nfds = epoll_wait(api->ep, api->events, loop->size, timeout);

    if (nfds > 0) {
        for (i = 0; i < nfds; i++) {
            struct epoll_event ee = api->events[i];
            int fd = ee.data.fd;
            struct event ev = loop->events[fd];

            int mask = 0;

            if (ee.events & EPOLLERR) mask |= EVENT_ERROR;
            if (ee.events & EPOLLIN) mask |= EVENT_READABLE;
            if (ee.events & EPOLLOUT) mask |= EVENT_WRITABLE;

            if (mask & EVENT_ERROR && ev.ecb != NULL)
                (ev.ecb)(loop, fd, mask, ev.data);
            if (mask & EVENT_READABLE && ev.rcb != NULL)
                (ev.rcb)(loop, fd, mask, ev.data);
            if (mask & EVENT_WRITABLE && ev.wcb != NULL)
                (ev.wcb)(loop, fd, mask, ev.data);
        }

        return EVENT_OK;
    }

    if (nfds == 0) {
        if (timeout == -1)
            return EVENT_EFAILED;
    }

    return EVENT_EFAILED;
}
