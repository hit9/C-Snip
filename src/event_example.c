// cc event_example.c event.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "event.h"

void
echo(struct event_loop *loop, int fd, int mask, void *data)
{
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

int
main(int argc, const char *argv[])
{
    /* allocate a new event loop with events number limitation 1024 */
    struct event_loop *loop = event_loop(1024);
    /* call `echo()` when stdin is readable (on data coming in) */
    event_add_in(loop, STDIN_FILENO, &echo, NULL);
    /* start event loop */
    printf("start event loop, type 'exit' to exit.. \n");
    event_loop_start(loop, -1);
    /* free event loop */
    event_loop_free(loop);
    return 0;
}
