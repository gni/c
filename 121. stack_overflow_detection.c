#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ucontext.h>

#define STACK_SIZE 1024

char stack[STACK_SIZE];

void signal_handler(int signum, siginfo_t *info, void *context) {
    printf("Stack overflow detected!\n");
    exit(1);
}

void setup_signal_handler() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(1);
    }
}

void recursive_function(int count) {
    char local[STACK_SIZE / 4]; // Large local allocation
    printf("Depth: %d\n", count);
    recursive_function(count + 1); // Infinite recursion
}

int main() {
    setup_signal_handler();
    recursive_function(1);
    return 0;
}
