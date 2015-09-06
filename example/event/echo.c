/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>
#include <unistd.h>

#include "event.h"

void
echo(struct event_loop *loop, int fd, int mask, void *data)
{
    char s[256];

    if (fd == STDIN_FILENO) {
        scanf("%s", s);
        printf("your input is: %s\n", s);
    }
}

int
main(int argc, const char *argv[])
{
    struct event_loop *loop = event_loop_new(1024);
    event_add_in(loop, STDIN_FILENO, &echo, NULL);
    event_loop_start(loop, -1);
    event_loop_free(loop);
    return 0;
}
