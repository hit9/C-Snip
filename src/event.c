/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "event.h"

#ifdef HAVE_EVPORT
#include "event_evport.c"
#else
    #ifdef HAVE_EPOLL
    #include "event_epoll.c"
    #else
        #ifdef HAVE_KQUEUE
        #include "event_kqueue.c"
        #else
        #include "event_select.c"
        #endif
    #endif
#endif
