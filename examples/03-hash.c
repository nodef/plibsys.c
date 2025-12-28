#define PLIBSYS_IMPLEMENTATION
#include "plibsys.h"
#include <stdio.h>
#include <string.h>

#define MD5_DIGEST_LENGTH 16

int main() {
    p_libsys_init();

    const char *data = "Hello, plibsys!";
    unsigned char hash[MD5_DIGEST_LENGTH];

    PCryptoHash *md5 = p_crypto_hash_new(P_CRYPTO_HASH_TYPE_MD5);
    if (md5 == NULL) {
        printf("Failed to create MD5 hash object\n");
        p_libsys_shutdown();
        return 1;
    }

    p_crypto_hash_update(md5, (const puchar *)data, strlen(data));

    psize len = MD5_DIGEST_LENGTH;
    p_crypto_hash_get_digest(md5, hash, &len);

    printf("MD5 hash of '%s': ", data);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    p_crypto_hash_free(md5);
    p_libsys_shutdown();
    return 0;
}
