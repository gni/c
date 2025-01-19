#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MESSAGE_QUEUE_KEY 1234
#define MESSAGE_SIZE 256

typedef struct {
    long type;
    char text[MESSAGE_SIZE];
} Message;

void node(int node_id, int queue_id) {
    Message msg;
    while (1) {
        if (msgrcv(queue_id, &msg, sizeof(msg.text), node_id, IPC_NOWAIT) > 0) {
            printf("Node %d received: %s\n", node_id, msg.text);
        }
        sleep(1);
    }
}

int main() {
    int queue_id = msgget(MESSAGE_QUEUE_KEY, IPC_CREAT | 0666);
    if (queue_id == -1) {
        perror("Error creating message queue");
        return 1;
    }

    if (fork() == 0) {
        node(1, queue_id);
        return 0;
    }
    if (fork() == 0) {
        node(2, queue_id);
        return 0;
    }

    Message msg;
    for (int i = 0; i < 5; i++) {
        msg.type = 1;
        snprintf(msg.text, MESSAGE_SIZE, "Hello from main to Node %d", 1);
        msgsnd(queue_id, &msg, sizeof(msg.text), 0);

        msg.type = 2;
        snprintf(msg.text, MESSAGE_SIZE, "Hello from main to Node %d", 2);
        msgsnd(queue_id, &msg, sizeof(msg.text), 0);

        sleep(2);
    }

    msgctl(queue_id, IPC_RMID, NULL); // Clean up message queue
    return 0;
}
