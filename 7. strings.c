#include <stdio.h>
#include <string.h> // For string functions

int main() {
    char name[20];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Hello, %s!\n", name);
    printf("Your name has %lu characters.\n", strlen(name)); // strlen gives string length

    return 0;
}
