#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Node {
    char key[50];
    char value[50];
    struct Node *next;
};

struct Node* hash_table[SIZE];

int hash(char *key) {
    int hash = 0;
    while (*key) {
        hash += *key;
        key++;
    }
    return hash % SIZE;
}

void insert(char *key, char *value) {
    int index = hash(key);
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(new_node->key, key);
    strcpy(new_node->value, value);
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

char* search(char *key) {
    int index = hash(key);
    struct Node *temp = hash_table[index];
    while (temp) {
        if (strcmp(temp->key, key) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL;
}

int main() {
    insert("name", "Alice");
    insert("age", "25");
    insert("city", "Paris");

    printf("Name: %s\n", search("name"));
    printf("Age: %s\n", search("age"));
    printf("City: %s\n", search("city"));

    return 0;
}
