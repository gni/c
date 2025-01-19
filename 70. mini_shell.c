#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void execute_command(char *command) {
    char *args[10];
    int i = 0;

    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " ");
    }

    if (fork() == 0) {
        execvp(args[0], args);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int main() {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("mini-shell> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "exit") == 0) break;
        execute_command(buffer);
    }
    return 0;
}
