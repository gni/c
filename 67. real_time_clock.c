#include <stdio.h>
#include <time.h>

int main() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("Seconds: %ld\nNanoseconds: %ld\n", ts.tv_sec, ts.tv_nsec);
    return 0;
}
