/*ouxiaobo*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"

int sha256_test()
{
    BYTE text1[] = { "abc" };
    BYTE hash1[SHA256_BLOCK_SIZE] = { 0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
                                     0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad };
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    int pass = 1;

    sha256_init(&ctx);
    sha256_update(&ctx, text1, strlen(text1));
    sha256_final(&ctx, buf);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        printf("%02x", buf[i]);
    }

    pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);
    return(pass);
}

int main()
{
    printf("SHA-256 tests: %s\n", sha256_test() ? "SUCCEEDED" : "FAILED");

    return(0);
}
