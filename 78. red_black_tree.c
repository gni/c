#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct RBNode {
    int data;
    NodeColor color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode *create_node(int data) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED; // New nodes are RED by default
    node->left = node->right = node->parent = NULL;
    return node;
}

// Rotate and balance functions here (e.g., left_rotate, right_rotate)

// Insert logic
RBNode *insert(RBNode *root, int data) {
    // Insert like a regular binary search tree
    // Then rebalance the tree and fix colors
    // (Implementation of balancing logic is complex and requires multiple cases)
    return root; // Placeholder
}

void print_tree(RBNode *root, int depth) {
    if (!root) return;
    print_tree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d (%s)\n", root->data, root->color == RED ? "R" : "B");
    print_tree(root->left, depth + 1);
}

int main() {
    RBNode *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);

    printf("Red-Black Tree:\n");
    print_tree(root, 0);
    return 0;
}
