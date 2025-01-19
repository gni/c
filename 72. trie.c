#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end_of_word;
} TrieNode;

TrieNode *create_node() {
    TrieNode *node = malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode *root, const char *key) {
    TrieNode *node = root;
    for (int i = 0; key[i]; i++) {
        int index = key[i] - 'a';
        if (!node->children[index]) {
            node->children[index] = create_node();
        }
        node = node->children[index];
    }
    node->is_end_of_word = 1;
}

int search(TrieNode *root, const char *key) {
    TrieNode *node = root;
    for (int i = 0; key[i]; i++) {
        int index = key[i] - 'a';
        if (!node->children[index]) return 0;
        node = node->children[index];
    }
    return node->is_end_of_word;
}

int main() {
    TrieNode *root = create_node();
    insert(root, "hello");
    insert(root, "world");

    printf("Searching for 'hello': %s\n", search(root, "hello") ? "Found" : "Not Found");
    printf("Searching for 'world': %s\n", search(root, "world") ? "Found" : "Not Found");
    printf("Searching for 'test': %s\n", search(root, "test") ? "Found" : "Not Found");

    return 0;
}
