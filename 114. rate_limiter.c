#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REQUESTS 5
#define TIME_WINDOW 10 // seconds

typedef struct {
    int request_count;
    time_t window_start;
} RateLimiter;

void init_rate_limiter(RateLimiter *limiter) {
    limiter->request_count = 0;
    limiter->window_start = time(NULL);
}

int allow_request(RateLimiter *limiter) {
    time_t now = time(NULL);
    if (now - limiter->window_start >= TIME_WINDOW) {
        limiter->request_count = 0;
        limiter->window_start = now;
    }

    if (limiter->request_count < MAX_REQUESTS) {
        limiter->request_count++;
        return 1; // Request allowed
    }
    return 0; // Request denied
}

int main() {
    RateLimiter limiter;
    init_rate_limiter(&limiter);

    for (int i = 0; i < 10; i++) {
        if (allow_request(&limiter)) {
            printf("Request %d allowed.\n", i + 1);
        } else {
            printf("Request %d denied.\n", i + 1);
        }
        sleep(1); // Simulate time between requests
    }

    return 0;
}
