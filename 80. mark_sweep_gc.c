#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Object {
    int id;
    bool marked;
    struct Object *next;
} Object;

typedef struct {
    Object *head;
} MemoryManager;

MemoryManager *create_manager() {
    MemoryManager *manager = malloc(sizeof(MemoryManager));
    manager->head = NULL;
    return manager;
}

Object *allocate_object(MemoryManager *manager, int id) {
    Object *obj = malloc(sizeof(Object));
    obj->id = id;
    obj->marked = false;
    obj->next = manager->head;
    manager->head = obj;
    return obj;
}

void mark(Object *obj) {
    if (!obj || obj->marked) return;
    obj->marked = true;
    // Recursively mark connected objects (if any).
}

void sweep(MemoryManager *manager) {
    Object **current = &manager->head;
    while (*current) {
        if (!(*current)->marked) {
            Object *unreachable = *current;
            *current = (*current)->next;
            free(unreachable);
        } else {
            (*current)->marked = false; // Reset for next GC cycle.
            current = &(*current)->next;
        }
    }
}

int main() {
    MemoryManager *manager = create_manager();

    Object *obj1 = allocate_object(manager, 1);
    Object *obj2 = allocate_object(manager, 2);
    Object *obj3 = allocate_object(manager, 3);

    mark(obj1); // Simulate marking live objects.
    sweep(manager); // Remove unmarked objects.

    free(manager);
    return 0;
}
