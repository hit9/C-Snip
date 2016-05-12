/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>

#include "datetime.h"

void case_datetime_stamp_now() {
    /* assert current timstamp must be greater than 1447502650543
     * (the stamp when I'm writing this test case) */
    assert(datetime_stamp_now() > 1447502650543);
    /* assert that the code will run so fast the two getting results
     * diff should smaller than 1ms */
    assert((long)datetime_stamp_now() == (long)datetime_stamp_now());
}
