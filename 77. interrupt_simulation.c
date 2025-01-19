#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signal) {
    printf("Interrupt received: %d\n", signal);
}

int main() {
    signal(SIGINT, handle_signal);
    printf("Press Ctrl+C to trigger interrupt.\n");

    while (1) {
        sleep(1);
    }
    return 0;
}
