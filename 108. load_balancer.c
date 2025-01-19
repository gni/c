#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SERVERS 3

// Structure to represent a server
typedef struct {
    int id;                 // Server ID
    int requests_handled;   // Number of requests handled by the server
} Server;

// Function to assign a request to the current server
void handle_request(Server *servers, int *current_server) {
    printf("Request assigned to server %d\n", servers[*current_server].id);
    servers[*current_server].requests_handled++;
    *current_server = (*current_server + 1) % NUM_SERVERS; // Move to the next server
}

// Function to print server statistics
void print_stats(Server *servers) {
    printf("\nServer statistics:\n");
    for (int i = 0; i < NUM_SERVERS; i++) {
        printf("Server %d: %d requests handled\n", servers[i].id, servers[i].requests_handled);
    }
    printf("\n");
}

int main() {
    Server servers[NUM_SERVERS];
    for (int i = 0; i < NUM_SERVERS; i++) {
        servers[i].id = i + 1;
        servers[i].requests_handled = 0;
    }

    int current_server = 0;
    int num_requests = 10; // Number of requests to simulate

    printf("Load Balancer Simulation...\n");
    for (int i = 0; i < num_requests; i++) {
        handle_request(servers, &current_server);
    }

    print_stats(servers);

    return 0;
}
