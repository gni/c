#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent, rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void union_set(Subset subsets[], int x, int y) {
    int root_x = find(subsets, x);
    int root_y = find(subsets, y);

    if (subsets[root_x].rank < subsets[root_y].rank) {
        subsets[root_x].parent = root_y;
    } else if (subsets[root_x].rank > subsets[root_y].rank) {
        subsets[root_y].parent = root_x;
    } else {
        subsets[root_y].parent = root_x;
        subsets[root_x].rank++;
    }
}

void kruskal_mst(Edge edges[], int V, int E) {
    qsort(edges, E, sizeof(Edge), [](const void *a, const void *b) {
        return ((Edge *)a)->weight - ((Edge *)b)->weight;
    });

    Subset *subsets = malloc(V * sizeof(Subset));
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    printf("Edges in MST:\n");
    for (int i = 0, e = 0; e < V - 1 && i < E; i++) {
        Edge next_edge = edges[i];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            printf("(%d -- %d) == %d\n", next_edge.src, next_edge.dest, next_edge.weight);
            union_set(subsets, x, y);
            e++;
        }
    }

    free(subsets);
}

int main() {
    int V = 4, E = 5;
    Edge edges[] = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

    kruskal_mst(edges, V, E);
    return 0;
}
