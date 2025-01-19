#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, value;
    struct Node *prev, *next;
} Node;

typedef struct {
    int capacity, size;
    Node *head, *tail;
    Node **hash_map;
} LRUCache;

LRUCache *create_cache(int capacity) {
    LRUCache *cache = malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    cache->hash_map = calloc(1000, sizeof(Node *));
    return cache;
}

void move_to_head(LRUCache *cache, Node *node) {
    if (cache->head == node) return;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (cache->tail == node) cache->tail = node->prev;

    node->next = cache->head;
    if (cache->head) cache->head->prev = node;
    node->prev = NULL;
    cache->head = node;
}

int get(LRUCache *cache, int key) {
    Node *node = cache->hash_map[key];
    if (!node) return -1;
    move_to_head(cache, node);
    return node->value;
}

void put(LRUCache *cache, int key, int value) {
    Node *node = cache->hash_map[key];
    if (node) {
        node->value = value;
        move_to_head(cache, node);
    } else {
        node = malloc(sizeof(Node));
        node->key = key;
        node->value = value;
        node->prev = node->next = NULL;

        if (cache->size == cache->capacity) {
            cache->hash_map[cache->tail->key] = NULL;
            cache->tail = cache->tail->prev;
            if (cache->tail) cache->tail->next = NULL;
            free(node);
        } else {
            cache->size++;
        }

        node->next = cache->head;
        if (cache->head) cache->head->prev = node;
        cache->head = node;
        if (!cache->tail) cache->tail = node;
        cache->hash_map[key] = node;
    }
}

int main() {
    LRUCache *cache = create_cache(2);

    put(cache, 1, 1);
    put(cache, 2, 2);
    printf("Get 1: %d\n", get(cache, 1));
    put(cache, 3, 3);
    printf("Get 2: %d\n", get(cache, 2));
    put(cache, 4, 4);
    printf("Get 1: %d\n", get(cache, 1));
    printf("Get 3: %d\n", get(cache, 3));
    printf("Get 4: %d\n", get(cache, 4));

    return 0;
}
