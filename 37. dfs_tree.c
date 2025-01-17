#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void dfs(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    dfs(root->left);
    dfs(root->right);
}

int main() {
    struct Node *root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);

    printf("DFS Traversal: ");
    dfs(root);
    printf("\n");

    return 0;
}
