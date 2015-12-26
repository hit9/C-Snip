/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "cfg.h"

void
case_cfg_get()
{
    char s[1024] = "# this is an proxy example cfg.\n"
                   "port 8125  # port to bind\n"
                   "# backend server nodes\n"
                   "node 127.0.0.1:8001\n";
    struct cfg cfg;
    cfg.data = s;
    cfg.len = strlen(s);
    cfg.lineno = 1;

    assert(cfg_get(&cfg) == CFG_OK);
    assert(strncmp("port", cfg.key, cfg.key_len) == 0);
    assert(strncmp("8125", cfg.val, cfg.val_len) == 0);

    assert(cfg_get(&cfg) == CFG_OK);
    assert(strncmp("node", cfg.key, cfg.key_len) == 0);
    assert(strncmp("127.0.0.1:8001", cfg.val, cfg.val_len) == 0);
}
