// cc event_example.c event.c

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "event.h"

void echo(struct event_loop *loop, int fd, int mask, void *data) {
    char s[256];

    if (fd == STDIN_FILENO) {
        scanf("%s", s);

        if (strcmp(s, "exit") == 0) {
            /* stop the event loop on message "exit" */
            printf("bye!\n");
            event_loop_stop(loop);
        } else {
            printf("your input is: %s\n", s);
        }
    }
}

void heartbeat(struct event_loop *loop, int id, void *data) {
    printf("heartbeat every 1000ms\n");
}

int main(int argc, const char *argv[]) {
    /* allocate a new event loop with events number limitation 1024 */
    struct event_loop *loop = event_loop(1024);
    /* call `echo()` when stdin is readable (on data coming in) */
    event_add_in(loop, STDIN_FILENO, &echo, NULL);
    /* call `heartbeat` every 1 second */
    event_add_timer(loop, 1000, &heartbeat, NULL);
    /* start event loop */
    printf("start event loop, type 'exit' to exit.. \n");
    event_loop_start(loop);
    /* free event loop */
    event_loop_free(loop);
    return 0;
}
