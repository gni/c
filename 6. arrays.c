#include <stdio.h>

int main() {
    int numbers[5] = {1, 2, 3, 4, 5}; // An array of 5 integers

    printf("The elements of the array are:\n");
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    return 0;
}
