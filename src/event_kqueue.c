/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include "event.h"

#define EVENT_KQUEUE_ALWAYS_CLEAR   1

struct event_api {
    int kp;                 /* kqueue descriptor */
    struct kevent *events;  /* struct kevent[], with size `loop->size` */
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

    api->kp = kqueue();

    if (api->kp < 0) {
        free(api);
        return EVENT_EFAILED;
    }

    api->events = malloc(sizeof(struct kevent) * loop->size);

    if (api->events == NULL) {
        close(api->kp);
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
        if (loop->api->kp > 0)
            close(loop->api->kp);
        if (loop->api->events != NULL)
            free(loop->api->events);
        free(loop->api);
    }
}

int
event_api_add(struct event_loop *loop, int fd, int mask)
{
    assert(loop != NULL);
    assert(loop->api != NULL);

    struct kevent ev;
    struct event_api *api = loop->api;

    int op = EV_ADD;

    if (EVENT_KQUEUE_ALWAYS_CLEAR)
        op |= EV_CLEAR;

    if (mask & EVENT_READABLE) {
        EV_SET(&ev, fd, EVFILT_READ, op, 0, 0, NULL);
        if (kevent(api->kp, &ev, 1, NULL, 0, NULL) < 0)
            return  EVENT_EFAILED;
    }

    if (mask & EVENT_WRITABLE) {
        EV_SET(&ev, fd, EVFILT_WRITE, op, 0, 0, NULL);
        if (kevent(api->kp, &ev, 1, NULL, 0, NULL) < 0)
            return EVENT_EFAILED;
    }
    return EVENT_OK;
}

int
event_api_del(struct event_loop *loop, int fd, int mask)
{
    assert(loop != NULL);
    assert(loop->api != NULL);

    struct kevent ev;
    struct event_api *api = loop->api;

    int op = EV_DELETE;

    if (EVENT_KQUEUE_ALWAYS_CLEAR)
        op |= EV_CLEAR;

    if (mask & EVENT_READABLE) {
        EV_SET(&ev, fd, EVFILT_READ, op, 0, 0, NULL);
        if (kevent(api->kp, &ev, 1, NULL, 0, NULL) < 0)
            return  EVENT_EFAILED;
    }

    if (mask & EVENT_WRITABLE) {
        EV_SET(&ev, fd, EVFILT_WRITE, op, 0, 0, NULL);
        if (kevent(api->kp, &ev, 1, NULL, 0, NULL) < 0)
            return EVENT_EFAILED;
    }

    return EVENT_OK;
}

int
event_api_wait(struct event_loop *loop, int timeout)
{
    assert(loop != NULL);

    struct event_api *api = loop->api;

    assert(api != NULL);
    assert(api->kp >= 0);

    int nfds;

    if (timeout >= 0 ) {
        struct timespec tv;
        tv.tv_sec = timeout / 1000;
        tv.tv_nsec = (timeout - tv.tv_sec * 1000) * 1000000;
        nfds = kevent(api->kp, NULL, 0, api->events, loop->size, &tv);
    } else {
        nfds = kevent(api->kp, NULL, 0, api->events, loop->size, NULL);
    }

    int i;

    if (nfds > 0) {
        for (i = 0; i < nfds; i++) {
            struct kevent ke = api->events[i];
            int fd = ke.ident;
            struct event ev = loop->events[fd];

            int mask = 0;

            if (ke.flags & EV_ERROR) mask |= EVENT_ERROR;
            if (ke.filter == EVFILT_READ) mask |= EVENT_READABLE;
            if (ke.filter == EVFILT_WRITE) mask |= EVENT_WRITABLE;

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
        if (timeout >= 0)
            return EVENT_OK;
    }

    return EVENT_EFAILED;
}
