#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_PROPOSERS 3
#define NUM_ACCEPTORS 3

// Struct for a proposal
typedef struct {
    int id;
    int value;
} Proposal;

// Struct for an acceptor's state
typedef struct {
    int highest_proposal_id;
    int accepted_value;
    int accepted_proposal_id;
} Acceptor;

// Struct for a proposer
typedef struct {
    int id;
    Proposal proposal;
} Proposer;

// Initialize acceptors
void init_acceptors(Acceptor acceptors[]) {
    for (int i = 0; i < NUM_ACCEPTORS; i++) {
        acceptors[i].highest_proposal_id = -1;
        acceptors[i].accepted_value = -1;
        acceptors[i].accepted_proposal_id = -1;
    }
}

// Propose a value
void propose(Proposer *proposer, Acceptor acceptors[]) {
    printf("Proposer %d proposing value %d (ID %d)\n", proposer->id, proposer->proposal.value, proposer->proposal.id);

    int promise_count = 0;
    int majority = (NUM_ACCEPTORS / 2) + 1;

    // Phase 1: Send proposal and collect promises
    for (int i = 0; i < NUM_ACCEPTORS; i++) {
        if (proposer->proposal.id > acceptors[i].highest_proposal_id) {
            acceptors[i].highest_proposal_id = proposer->proposal.id;
            promise_count++;
        }
    }

    if (promise_count >= majority) {
        // Phase 2: Send accept requests
        printf("Proposer %d has majority promises. Sending accept requests...\n", proposer->id);
        int accept_count = 0;

        for (int i = 0; i < NUM_ACCEPTORS; i++) {
            if (acceptors[i].highest_proposal_id == proposer->proposal.id) {
                acceptors[i].accepted_value = proposer->proposal.value;
                acceptors[i].accepted_proposal_id = proposer->proposal.id;
                accept_count++;
            }
        }

        if (accept_count >= majority) {
            printf("Proposer %d: Value %d accepted by majority.\n", proposer->id, proposer->proposal.value);
        } else {
            printf("Proposer %d: Failed to achieve majority acceptance.\n", proposer->id);
        }
    } else {
        printf("Proposer %d: Failed to achieve majority promises.\n", proposer->id);
    }
}

// Simulate the Paxos algorithm
void simulate_paxos() {
    Acceptor acceptors[NUM_ACCEPTORS];
    init_acceptors(acceptors);

    Proposer proposers[NUM_PROPOSERS];
    srand(time(NULL));

    // Initialize proposers with random values
    for (int i = 0; i < NUM_PROPOSERS; i++) {
        proposers[i].id = i + 1;
        proposers[i].proposal.id = rand() % 100; // Random proposal ID
        proposers[i].proposal.value = rand() % 1000; // Random proposal value
    }

    // Proposers propose values
    for (int i = 0; i < NUM_PROPOSERS; i++) {
        propose(&proposers[i], acceptors);
    }
}

int main() {
    printf("Paxos Consensus Algorithm Simulation\n");
    simulate_paxos();
    return 0;
}
