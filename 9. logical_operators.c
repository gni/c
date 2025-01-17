#include <stdio.h>

int main() {
    int a = 5, b = 10;

    if (a > 0 && b > 0) {
        printf("Both a and b are positive numbers.\n");
    }

    if (a < 0 || b < 0) {
        printf("At least one of the numbers is negative.\n");
    } else {
        printf("Neither a nor b is negative.\n");
    }

    if (!(a == b)) {
        printf("a and b are not equal.\n");
    }

    return 0;
}
