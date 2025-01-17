#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node* create_node(int data) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->prev = new_node->next = NULL;
    return new_node;
}

void print_list(struct Node *head) {
    struct Node *temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node *head = create_node(10);
    struct Node *second = create_node(20);
    struct Node *third = create_node(30);

    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;

    print_list(head);

    return 0;
}
