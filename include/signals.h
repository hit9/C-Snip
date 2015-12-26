/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Signals hanlder util.
 * deps: None.
 */

#ifndef _CW_SIGNALS_H
#define _CW_STGNALS_H  1

#include <signal.h>

#if defined(__cplusplus)
extern "C" {
#endif

void
signals_register(int signal, void (*handler)(int))
{
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
