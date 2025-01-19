#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PROCESSES 5
#define TIME_QUANTUM 2

typedef struct {
    int id;
    int burst_time;
    int remaining_time;
} Process;

void simulate_round_robin(Process processes[], int n) {
    int time = 0;
    int all_done;

    do {
        all_done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                all_done = 0;
                int exec_time = (processes[i].remaining_time > TIME_QUANTUM) ? TIME_QUANTUM : processes[i].remaining_time;
                printf("Process %d executed for %d units.\n", processes[i].id, exec_time);
                processes[i].remaining_time -= exec_time;
                time += exec_time;
            }
        }
    } while (!all_done);

    printf("All processes completed. Total time: %d units.\n", time);
}

int main() {
    Process processes[MAX_PROCESSES] = {
        {1, 5, 5}, {2, 8, 8}, {3, 3, 3}, {4, 6, 6}, {5, 2, 2}
    };

    printf("Simulating round-robin scheduling...\n");
    simulate_round_robin(processes, MAX_PROCESSES);

    return 0;
}
