// cc event_timer_example.c event.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "event.h"

void
beat1000(struct event_loop *loop, int id, void *data)
{
    printf("heartbeat every 1s\n");
}

void
beat2000(struct event_loop *loop, int id, void *data)
{
    printf("heartbeat every 2s\n");
}

void
beat3000(struct event_loop *loop, int id, void *data)
{
    printf("heartbeat every 3s\n");
}

void
beatonce(struct event_loop *loop, int id, void *data)
{
    printf("heartbeat only once after 5s\n");
    /* stop this timer */
    event_del_timer(loop, id);
}

int
main(int argc, const char *argv[])
{
    /* allocate a new event loop with no fire events */
    struct event_loop *loop = event_loop(0);
    /* add some timer events */
    event_add_timer(loop, 1000, &beat1000, NULL);
    event_add_timer(loop, 2000, &beat2000, NULL);
    event_add_timer(loop, 3000, &beat3000, NULL);
    event_add_timer(loop, 5000, &beatonce, NULL);
    /* start event loop */
    event_loop_start(loop);
    /* free event loop */
    event_loop_free(loop);
    return 0;
}
