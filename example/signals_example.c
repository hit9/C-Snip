// cc signals_example.c event.c
#include <stdio.h>
#include "event.h"
#include "signals.h"

void on_keyboardinterrupt(int signal) { printf("keyboardinterrupt!\n"); }
void on_signalterm(int signal) { printf("signal term received!\n"); }
void beat1000(struct event_loop *loop, int id, void *data) {
    printf("heartbeat every 1s\n");
}

int main(int argc, const char *argv[]) {
    signals_register(SIGINT, &on_keyboardinterrupt);
    signals_register(SIGTERM, &on_signalterm);
    /* forever event loop to heart-beat every 10s */
    struct event_loop *loop = event_loop(0);
    event_add_timer(loop, 1000, &beat1000, NULL);
    event_loop_start(loop);
    event_loop_free(loop);
    return 0;
}
