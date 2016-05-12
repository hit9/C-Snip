// cc md5_example.c md5.c

#include <stdio.h>
#include <string.h>
#include "md5.h"

int main(int argc, const char *argv[]) {
    char *key = "key";
    unsigned long len = strlen(key);
    /* get hashing number by key */
    printf("md5 hash for 'key': %u\n", hash_md5(key, len));
    /* get md5 signatures (16) */
    unsigned char results[16];
    md5_signature((unsigned char *)key, len, results);
    int i;
    for (i = 0; i < 16; i++) printf("%x", results[i]);
    return 0;
}
