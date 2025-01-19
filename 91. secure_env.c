#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secure_zero(char *buffer, size_t length) {
    volatile char *p = buffer;
    while (length--) {
        *p++ = 0;
    }
}

int main() {
    const char *password = getenv("SECRET_PASSWORD");
    if (!password) {
        fprintf(stderr, "Error: SECRET_PASSWORD not set\n");
        return 1;
    }

    printf("Password loaded: %s\n", password);

    // Securely erase memory
    secure_zero((char *)password, strlen(password));

    return 0;
}
