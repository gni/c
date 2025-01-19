#include "encryption.h"
#include <string.h>

// Simple XOR encryption
void xor_encrypt(char *data, size_t length, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < length; i++) {
        data[i] ^= key[i % key_len];
    }
}
