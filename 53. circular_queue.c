#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int data[MAX];
    int front, rear, size;
} CircularQueue;

void init_queue(CircularQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int is_full(CircularQueue *q) {
    return q->size == MAX;
}

int is_empty(CircularQueue *q) {
    return q->size == 0;
}

void enqueue(CircularQueue *q, int value) {
    if (is_full(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = value;
    q->size++;
}

int dequeue(CircularQueue *q) {
    if (is_empty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return value;
}

void print_queue(CircularQueue *q) {
    if (is_empty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0, idx = q->front; i < q->size; i++) {
        printf("%d ", q->data[idx]);
        idx = (idx + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularQueue q;
    init_queue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    print_queue(&q);

    dequeue(&q);
    dequeue(&q);
    enqueue(&q, 60);

    print_queue(&q);
    return 0;
}
