#include <stdio.h>

void add(int a, int b) {
    printf("Sum: %d\n", a + b);
}

void subtract(int a, int b) {
    printf("Difference: %d\n", a - b);
}

void multiply(int a, int b) {
    printf("Product: %d\n", a * b);
}

void divide(int a, int b) {
    if (b != 0)
        printf("Quotient: %.2f\n", (float)a / b);
    else
        printf("Division by zero is not allowed.\n");
}

int main() {
    int choice, x, y;

    printf("Simple Calculator\n");
    printf("1. Add\n2. Subtract\n3. Multiply\n4. Divide\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);

    switch (choice) {
        case 1:
            add(x, y);
            break;
        case 2:
            subtract(x, y);
            break;
        case 3:
            multiply(x, y);
            break;
        case 4:
            divide(x, y);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
