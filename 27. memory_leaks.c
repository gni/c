#include <stdlib.h>
int main() {
    int *ptr = malloc(sizeof(int)); // Allocated but not freed
    *ptr = 10;
    return 0; // Memory leak!
}
