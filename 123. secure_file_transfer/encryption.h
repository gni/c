#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stddef.h> // Include for size_t

void xor_encrypt(char *data, size_t length, const char *key);

#endif