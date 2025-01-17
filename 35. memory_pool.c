#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 1024

char memory_pool[POOL_SIZE];
int pool_index = 0;

void* pool_alloc(size_t size) {
    if (pool_index + size > POOL_SIZE) {
        printf("Memory pool overflow!\n");
        return NULL;
    }
    void *ptr = &memory_pool[pool_index];
    pool_index += size;
    return ptr;
}

void pool_reset() {
    pool_index = 0;
}

int main() {
    char *str1 = (char *)pool_alloc(100);
    strcpy(str1, "Hello, Memory Pool!");
    printf("%s\n", str1);

    pool_reset(); // Reuse memory
    char *str2 = (char *)pool_alloc(200);
    strcpy(str2, "Memory Pool Reused!");
    printf("%s\n", str2);

    return 0;
}
