#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *name = "shared_memory";
    const size_t size = 1024;

    // Create shared memory
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, size);

    // Map shared memory
    void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Write to shared memory
    sprintf(ptr, "Hello from process %d!", getpid());

    printf("Data written: %s\n", (char *)ptr);

    // Unlink shared memory
    munmap(ptr, size);
    shm_unlink(name);

    return 0;
}
