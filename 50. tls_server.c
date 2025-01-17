#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>

int main() {
    SSL_library_init();
    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());

    if (!ctx) {
        printf("Failed to create SSL context.\n");
        return 1;
    }

    SSL_CTX_free(ctx);
    return 0;
}
