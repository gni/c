#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void handle_errors() {
    fprintf(stderr, "Error occurred.\n");
    exit(1);
}

void aes_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, unsigned char *iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handle_errors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handle_errors();

    int len;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, strlen((char *)plaintext))) handle_errors();

    int ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handle_errors();
    ciphertext_len += len;

    ciphertext[ciphertext_len] = '\0';
    EVP_CIPHER_CTX_free(ctx);
}

void aes_decrypt(const unsigned char *ciphertext, const unsigned char *key, unsigned char *plaintext, unsigned char *iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handle_errors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handle_errors();

    int len;
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, strlen((char *)ciphertext))) handle_errors();

    int plaintext_len = len;
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handle_errors();
    plaintext_len += len;

    plaintext[plaintext_len] = '\0';
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char key[32], iv[16];
    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    unsigned char plaintext[] = "Hello, AES Encryption!";
    unsigned char ciphertext[128], decryptedtext[128];

    aes_encrypt(plaintext, key, ciphertext, iv);
    printf("Ciphertext: %s\n", ciphertext);

    aes_decrypt(ciphertext, key, decryptedtext, iv);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
