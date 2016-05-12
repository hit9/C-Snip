/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * md5 hash function.
 * deps: None.
 */

/*
 * This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
 * MD5 Message-Digest Algorithm (RFC 1321).
 *
 * Homepage:
 * http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
 *
 * Author: Alexander Peslyak, better known as Solar Designer <solar at
 * openwall.com>
 */

#ifndef _CW_MD5_H
#define _CW_MD5_H 1

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

void md5_signature(unsigned char *key, unsigned long length,
                   unsigned char *result);
uint32_t hash_md5(const char *key, size_t key_length);

#if defined(__cplusplus)
}
#endif

#endif
