/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "event.h"

int fds[2];

void *write_data(void *data) {
    usleep(1000);
    char buf[256] = "abcdef";
    assert(write(fds[1], buf, 6) == 6);
    return NULL;
}

void read_data(struct event_loop *loop, int fd, int mask, void *data) {
    char buf[256];

    if (fd == fds[0]) {
        assert(read(fd, buf, 6) == 6);
        assert(strcmp(buf, "abcdef") == 0);
        event_loop_stop(loop);
    }
}

void case_event_simple() {
    assert(pipe(fds) == 0);

    struct event_loop *loop = event_loop_new(100);
    event_add_in(loop, fds[0], &read_data, NULL);

    pthread_t t;
    pthread_create(&t, NULL, &write_data, NULL);

    event_loop_start(loop);
    event_loop_free(loop);

    pthread_join(t, NULL);
}
