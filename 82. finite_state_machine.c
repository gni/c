#include <stdio.h>
#include <unistd.h>

typedef enum { RED, GREEN, YELLOW } State;

void display_state(State state) {
    switch (state) {
        case RED: printf("RED light\n"); break;
        case GREEN: printf("GREEN light\n"); break;
        case YELLOW: printf("YELLOW light\n"); break;
    }
}

State next_state(State current) {
    switch (current) {
        case RED: return GREEN;
        case GREEN: return YELLOW;
        case YELLOW: return RED;
    }
    return RED; // Default
}

int main() {
    State state = RED;

    for (int i = 0; i < 10; i++) {
        display_state(state);
        sleep(2); // Simulate delay
        state = next_state(state);
    }
    return 0;
}
