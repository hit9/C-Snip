/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Event loop wrapper.
 */

#ifndef _CW_EVENT_H
#define _CW_EVENT_H  1

#if defined(__cplusplus)
extern "C" {
#endif

#define EVENT_MIN_RESERVED_FDS  32
#define EVENT_FDSET_INCR        96

#define EVENT_READABLE  0x01  // 001
#define EVENT_WRITABLE  0x02  // 010
#define EVENT_ET        0x04  // 100

#ifdef __linux__
#define HAVE_EPOLL      1
#endif

#if (defined(__apple__) && defined(mac_os_x_version_10_6)) || defined(__freebsd__) || defined(__openbsd__) || defined (__netbsd__)
#define HAVE_KQUEUE     1
#endif

#ifdef __sun
#include <sys/feature_tests.h>
#ifdef _dtrace_version
#define HAVE_EVPORT     1
#endif
#endif

enum {
    EVENT_OK = 0,
    EVENT_ENOMEM = 1,
    EVENT_EFAILED = 2,
    EVENT_ERANGE = 3,
};

typedef int (*event_cb_t)(int fd, int op, void *data);

struct event_data {
    int op;                         /* one of EVENT_(READABLE|WRITABLE) */
    event_cb_t cb;                  /* event callback */
    void *data;                     /* user defined data */
};

#ifdef HAVE_EPOLL
#include <sys/epoll.h>

struct event_loop {
    int ep;                         /* epoll descriptor */
    struct epoll_event *events;     /* events to poll */
    int nevents;                    /* events[] length */
};
#endif

struct event_loop *event_loop_new(int size);
void event_loop_free(struct event_loop *loop);
int event_loop_add(struct event_loop *loop, int fd, int op,
        event_cb_t cb, void *data);

#if defined(__cplusplus)
}
#endif

#endif
