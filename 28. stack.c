#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Stack {
    int top;
    int data[MAX];
};

void push(struct Stack *stack, int value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int main() {
    struct Stack stack = { .top = -1 };

    push(&stack, 10);
    push(&stack, 20);
    printf("Popped: %d\n", pop(&stack));
    printf("Popped: %d\n", pop(&stack));
    printf("Popped: %d\n", pop(&stack)); // Underflow example

    return 0;
}
