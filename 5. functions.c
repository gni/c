#include <stdio.h>

// Function declaration
void greet(); 
int add(int a, int b);

int main() {
    greet();

    int sum = add(3, 7);
    printf("Sum: %d\n", sum);

    return 0;
}

// Function definition
void greet() {
    printf("Hello! Welcome to functions in C.\n");
}

int add(int a, int b) {
    return a + b;
}
