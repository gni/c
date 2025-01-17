#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) { // Child process
        close(fd[0]); // Close read end
        char message[] = "Hello from child!";
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
    } else { // Parent process
        close(fd[1]); // Close write end
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd[0]);
    }

    return 0;
}
