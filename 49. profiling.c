#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();

    for (int i = 0; i < 100000000; i++); // Simulate work

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed);
    return 0;
}
