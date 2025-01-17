#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int signal) {
    printf("Received signal %d. Exiting safely.\n", signal);
    exit(0);
}

int main() {
    signal(SIGINT, handle_signal); // Handle Ctrl+C
    printf("Press Ctrl+C to stop the program.\n");

    while (1) {
        // Infinite loop
    }

    return 0;
}



// 2nd option.
// #include <stdio.h>
// #include <signal.h>

// void custom_handler(int sig) {
//     printf("Caught signal %d. Performing custom action.\n", sig);
//     signal(sig, SIG_DFL); // Reset to default handler
// }

// int main() {
//     signal(SIGINT, custom_handler); // Handle Ctrl+C
//     while (1);
//     return 0;
// }
