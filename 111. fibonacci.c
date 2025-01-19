#include <stdio.h>

// Recursive implementation
long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Iterative implementation
long long fibonacci_iterative(int n) {
    if (n <= 1) return n;
    long long prev = 0, curr = 1, next;
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main() {
    int n;

    printf("Enter the position of Fibonacci sequence: ");
    scanf("%d", &n);

    printf("Fibonacci (Recursive): %lld\n", fibonacci_recursive(n));
    printf("Fibonacci (Iterative): %lld\n", fibonacci_iterative(n));

    return 0;
}
