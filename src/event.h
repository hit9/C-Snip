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

#define EVENT_NONE      0x00  // 0000
#define EVENT_READABLE  0x01  // 0001
#define EVENT_WRITABLE  0x02  // 0010
#define EVENT_ET        0x04  // 0100
#define EVENT_ERROR     0x08  // 1000

#define EVENT_LOOP_RUNNING  0
#define EVENT_LOOP_STOPPED  1

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

#define event_add_in(loop, fd, cb, data)    event_add(loop, fd, EVENT_READABLE, cb, data);
#define event_add_out(loop, fd, cb, data)   event_add(loop, fd, EVENT_WRITABLE, cb, data);
#define event_del_in(loop, fd)              event_del(loop, fd, EVENT_READABLE);
#define event_del_out(loop, fd)             event_del(loop, fd, EVENT_WRITABLE);

enum {
    EVENT_OK = 0,
    EVENT_ENOMEM = 1,
    EVENT_EFAILED = 2,
    EVENT_ERANGE = 3,
};

struct event_loop;
struct event_api;

typedef void (*event_cb_t)(struct event_loop *loop, int fd, int mask, void *data);

struct event {
    int mask;        /* EVENT_(NONE|READABLE|WRITABLE..) */
    event_cb_t rcb;  /* callback function on EVENT_READABLE */
    event_cb_t wcb;  /* callback function on EVENT_WRITABLE */
    event_cb_t ecb;  /* callback function on EVENT_ERROR */
    void *data;      /* user defined data */
};

struct event_loop {
    int size;                /* the max number of fds to track */
    int state;               /* one of EVENT_LOOP_(STOPPED|RUNNING) */
    struct event *events;    /* struct event[] */
    struct event_api *api;   /* to be implemented */
};

struct event_loop *event_loop_new(int size);
void event_loop_free(struct event_loop *loop);
int event_loop_start(struct event_loop *loop, int timeout);
void event_loop_stop(struct event_loop *loop);
int event_add(struct event_loop *loop, int fd, int mask,
        event_cb_t cb, void *data);
int event_del(struct event_loop *loop, int fd, int mask);
int event_wait(struct event_loop *loop, int timeout);

#if defined(__cplusplus)
}
#endif

#endif
