/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>

#include "cfg.h"

/* Get key and val from cfg. */
int cfg_get(struct cfg *cfg) {
    assert(cfg != NULL);
    assert(cfg->lineno > 0);

    if (cfg->data == NULL || cfg->len == 0) return CFG_EOF;

    char *data = cfg->data;
    size_t len = cfg->len;
    size_t idx = 0;

    cfg->key = NULL;
    cfg->val = NULL;
    cfg->key_len = 0;
    cfg->val_len = 0;

    while (idx < len) {
        switch (data[idx]) {
            case '\t':
            case ' ':
                if (cfg->key != NULL && cfg->key_len == 0) /* key end */
                    cfg->key_len = data + idx - cfg->key;
                if (cfg->val != NULL && cfg->val_len == 0) /* val end */
                    cfg->val_len = data + idx - cfg->val;
                break;
            case '\n':
                if (cfg->val != NULL && cfg->val_len == 0) /* val end */
                    cfg->val_len = data + idx - cfg->val;
                if (cfg->key_len != 0 && cfg->val_len != 0)
                    /* line end ok with key & val */
                    return CFG_OK;
                if (cfg->key != NULL && cfg->val == NULL)
                    /* line contains only one word */
                    return CFG_EBADFMT;
                cfg->lineno++;
                break;
            case '#':
                if (cfg->val != NULL && cfg->val_len == 0) /* val end */
                    cfg->val_len = data + idx - cfg->val;

                while (idx + 1 < len && data[idx + 1] != '\n') {
                    idx++;
                    cfg->data++;
                    cfg->len--;
                }
                break;
            default:
                if (cfg->key == NULL) /* key start */
                    cfg->key = data + idx;
                if (cfg->val == NULL && cfg->key_len != 0) /* val start */
                    cfg->val = data + idx;
                if (cfg->key_len != 0 && cfg->val_len != 0)
                    /* bad char after key and val */
                    return CFG_EBADFMT;
                break;
        }

        idx++;
        cfg->data++;
        cfg->len--;
    };

    return CFG_EOF;
}
