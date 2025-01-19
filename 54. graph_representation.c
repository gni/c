#include <stdio.h>
#include <stdlib.h>

#define MAX 5

void adjacency_matrix() {
    int graph[MAX][MAX] = {0};

    // Add edges
    graph[0][1] = 1;
    graph[1][2] = 1;
    graph[2][3] = 1;

    printf("Adjacency Matrix:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void adjacency_list() {
    struct Node {
        int vertex;
        struct Node *next;
    };

    struct Node *graph[MAX] = {NULL};

    // Add edge (0 -> 1)
    struct Node *node = malloc(sizeof(struct Node));
    node->vertex = 1;
    node->next = NULL;
    graph[0] = node;

    // Print adjacency list
    printf("Adjacency List:\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d: ", i);
        struct Node *temp = graph[i];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    adjacency_matrix();
    adjacency_list();
    return 0;
}
