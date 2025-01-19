#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Slab {
    size_t object_size;
    size_t slab_size;
    void **free_list;
    size_t free_count;
    char *data;
} Slab;

Slab *create_slab(size_t object_size, size_t slab_size) {
    Slab *slab = malloc(sizeof(Slab));
    slab->object_size = object_size;
    slab->slab_size = slab_size;
    slab->free_list = malloc(slab_size * sizeof(void *));
    slab->data = malloc(object_size * slab_size);
    slab->free_count = slab_size;

    for (size_t i = 0; i < slab_size; i++) {
        slab->free_list[i] = slab->data + i * object_size;
    }
    return slab;
}

void *slab_alloc(Slab *slab) {
    if (slab->free_count == 0) return NULL;
    return slab->free_list[--slab->free_count];
}

void slab_free(Slab *slab, void *obj) {
    slab->free_list[slab->free_count++] = obj;
}

void destroy_slab(Slab *slab) {
    free(slab->free_list);
    free(slab->data);
    free(slab);
}

int main() {
    Slab *slab = create_slab(32, 10);

    void *obj1 = slab_alloc(slab);
    void *obj2 = slab_alloc(slab);

    printf("Allocated objects: %p, %p\n", obj1, obj2);

    slab_free(slab, obj1);
    slab_free(slab, obj2);

    destroy_slab(slab);
    return 0;
}
