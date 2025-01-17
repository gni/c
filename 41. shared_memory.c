#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = 1234;
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *data = (char*) shmat(shmid, NULL, 0);

    if (fork() == 0) { // Child process
        strcpy(data, "Hello from child!");
        shmdt(data);
    } else { // Parent process
        sleep(1); // Wait for child
        printf("Parent read: %s\n", data);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL); // Cleanup
    }

    return 0;
}
