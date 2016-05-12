/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <string.h>

#include "utils.h"

void case_utils_min() {
    assert(MIN(1, 3) == 1);
    assert(MIN(1, -3) == -3);
}

void case_utils_max() {
    assert(MAX(1, 3) == 3);
    assert(MAX(1, -3) == 1);
}
