#include <stdio.h>

int main() {
    int numbers[5] = {10, 20, 5, 40, 15};
    int max = numbers[0];

    for (int i = 1; i < 5; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    printf("The largest number is: %d\n", max);

    return 0;
}
