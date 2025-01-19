#include <stdio.h>
#include <time.h>

void delay(int milliseconds) {
    long pause;
    clock_t now, start;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    start = clock();
    do {
        now = clock();
    } while ((now - start) < pause);
}

int main() {
    printf("Starting timer...\n");
    delay(2000); // 2-second delay
    printf("Timer ended.\n");
    return 0;
}
