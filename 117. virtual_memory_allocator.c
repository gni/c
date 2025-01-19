#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1024 // Simulated memory size

char memory[MEMORY_SIZE];
char allocation_map[MEMORY_SIZE];

void init_memory() {
    memset(memory, 0, MEMORY_SIZE);
    memset(allocation_map, 0, MEMORY_SIZE);
}

void *allocate(size_t size) {
    for (size_t i = 0; i < MEMORY_SIZE - size; i++) {
        int free = 1;
        for (size_t j = 0; j < size; j++) {
            if (allocation_map[i + j]) {
                free = 0;
                break;
            }
        }
        if (free) {
            memset(allocation_map + i, 1, size);
            return memory + i;
        }
    }
    return NULL; // No sufficient memory
}

void deallocate(void *ptr, size_t size) {
    size_t offset = (char *)ptr - memory;
    memset(allocation_map + offset, 0, size);
}

int main() {
    init_memory();

    void *ptr1 = allocate(128);
    void *ptr2 = allocate(64);
    if (ptr1 && ptr2) {
        printf("Memory allocated.\n");
        strcpy(ptr1, "Hello, Virtual Memory!");
        printf("Stored in memory: %s\n", (char *)ptr1);
    } else {
        printf("Memory allocation failed.\n");
    }

    deallocate(ptr1, 128);
    deallocate(ptr2, 64);
    printf("Memory deallocated.\n");

    return 0;
}
