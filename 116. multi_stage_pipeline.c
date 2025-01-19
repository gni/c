#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <keyword> <file>\n", argv[0]);
        return 1;
    }

    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) error_exit("pipe");

    pid_t pid1 = fork();
    if (pid1 == 0) { // First child: cat file
        close(pipe1[0]); // Close read end
        dup2(pipe1[1], STDOUT_FILENO);
        execlp("cat", "cat", argv[2], NULL);
        error_exit("cat");
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Second child: grep keyword
        close(pipe1[1]); // Close write end of first pipe
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe2[0]); // Close read end of second pipe
        dup2(pipe2[1], STDOUT_FILENO);
        execlp("grep", "grep", argv[1], NULL);
        error_exit("grep");
    }

    close(pipe1[0]); close(pipe1[1]); // Parent: close pipe1
    close(pipe2[1]); // Close write end of second pipe
    dup2(pipe2[0], STDIN_FILENO);
    execlp("wc", "wc", "-l", NULL); // Final stage: wc -l
    error_exit("wc");

    return 0;
}
