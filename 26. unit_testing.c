#include <assert.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    assert(add(2, 3) == 5); // Pass
    assert(add(2, 3) == 6); // Fail (this will stop the program)
    return 0;
}
