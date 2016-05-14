/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Signals hanlder util.
 * deps: None.
 */

#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include <signal.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

void signals_register(int signal, void (*handler)(int)) {
    struct sigaction signal_action;
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = 0;
    signal_action.sa_handler = handler;
    sigaction(signal, &signal_action, NULL);
}

#if defined(__cplusplus)
}
#endif

#endif
