#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 4

// Structure to represent a process
typedef struct {
    int id;           // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time;   // Burst time (execution time required)
    int remaining_time; // Time left to complete
    int completion_time; // Completion time
    bool is_completed;   // Flag to check if the process is completed
} Process;

// Function to simulate the Round-Robin scheduling
void round_robin_scheduler(Process processes[], int num_processes, int time_quantum) {
    int current_time = 0;
    bool all_completed;

    printf("Time | Executing Process | Remaining Time\n");
    printf("------------------------------------------------\n");

    while (true) {
        all_completed = true;

        for (int i = 0; i < num_processes; i++) {
            if (!processes[i].is_completed) {
                all_completed = false;

                if (processes[i].remaining_time > 0) {
                    printf("%4d | Process %d        | %4d\n", current_time, processes[i].id, processes[i].remaining_time);

                    if (processes[i].remaining_time <= time_quantum) {
                        current_time += processes[i].remaining_time;
                        processes[i].remaining_time = 0;
                        processes[i].completion_time = current_time;
                        processes[i].is_completed = true;

                        printf("%4d | Process %d        | Completed\n", current_time, processes[i].id);
                    } else {
                        current_time += time_quantum;
                        processes[i].remaining_time -= time_quantum;
                    }
                }
            }
        }

        if (all_completed) {
            break;
        }
    }

    printf("------------------------------------------------\n");
}

// Function to display process information
void display_process_info(Process processes[], int num_processes) {
    printf("\nProcess Information:\n");
    printf("ID | Arrival Time | Burst Time | Completion Time\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < num_processes; i++) {
        printf("%2d | %12d | %10d | %15d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time);
    }
}

int main() {
    Process processes[MAX_PROCESSES];
    int num_processes;

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &num_processes);

    if (num_processes > MAX_PROCESSES || num_processes <= 0) {
        printf("Invalid number of processes. Exiting.\n");
        return 1;
    }

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        printf("Process %d: Arrival Time: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Process %d: Burst Time: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = false;
    }

    printf("\nStarting Round-Robin Scheduling with Time Quantum: %d\n", TIME_QUANTUM);
    round_robin_scheduler(processes, num_processes, TIME_QUANTUM);

    display_process_info(processes, num_processes);

    return 0;
}
