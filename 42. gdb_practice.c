#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i <= 5; i++) { // Bug: out-of-bounds access
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}

// gcc -g 42.gdb_practice.c -o gdb_practice
// gdb ./gdb_practice