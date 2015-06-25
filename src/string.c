/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include "string.h"

bool
string_is_empty(struct string *s)
{
    if (s->len == 0) {
        assert(s->data == NULL);
        return true;
    } else {
        assert(s->data != NULL);
        return false;
    }
}
