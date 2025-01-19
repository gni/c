#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size, capacity;
} MinHeap;

MinHeap *create_heap(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->data = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heapify_up(MinHeap *heap, int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (heap->data[parent] > heap->data[index]) {
        int temp = heap->data[parent];
        heap->data[parent] = heap->data[index];
        heap->data[index] = temp;
        heapify_up(heap, parent);
    }
}

void insert(MinHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full!\n");
        return;
    }
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
}

void print_heap(MinHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    MinHeap *heap = create_heap(10);
    insert(heap, 3);
    insert(heap, 1);
    insert(heap, 6);
    insert(heap, 5);
    insert(heap, 2);
    insert(heap, 4);

    printf("Heap: ");
    print_heap(heap);

    free(heap->data);
    free(heap);
    return 0;
}
