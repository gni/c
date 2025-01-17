#include <stdio.h>

int main() {
    int age;
    float height;
    char name[20];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your height: ");
    scanf("%f", &height);

    printf("\nHello %s!\n", name);
    printf("You are %d years old and %.2f meters tall.\n", age, height);

    return 0;
}
