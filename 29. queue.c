#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Queue {
    int front, rear;
    int data[MAX];
};

void enqueue(struct Queue *queue, int value) {
    if (queue->rear == MAX - 1) {
        printf("Queue overflow!\n");
        return;
    }
    queue->data[++queue->rear] = value;
}

int dequeue(struct Queue *queue) {
    if (queue->front > queue->rear) {
        printf("Queue underflow!\n");
        return -1;
    }
    return queue->data[queue->front++];
}

int main() {
    struct Queue queue = { .front = 0, .rear = -1 };

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    printf("Dequeued: %d\n", dequeue(&queue));
    printf("Dequeued: %d\n", dequeue(&queue));
    printf("Dequeued: %d\n", dequeue(&queue)); // Underflow example

    return 0;
}
