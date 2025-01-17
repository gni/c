#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path = getenv("PATH");
    printf("PATH: %s\n", path);

    setenv("MY_VAR", "Hello, Environment!", 1);
    printf("MY_VAR: %s\n", getenv("MY_VAR"));
    return 0;
}
