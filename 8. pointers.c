#include <stdio.h>

int main() {
    int num = 10;
    int *ptr = &num; // Pointer to num

    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", &num); // %p prints addresses
    printf("Value at pointer ptr: %d\n", *ptr); // Dereference pointer

    return 0;
}
