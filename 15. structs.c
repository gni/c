#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

int main() {
    struct Student s1;

    strcpy(s1.name, "Alice");
    s1.age = 20;
    s1.grade = 3.8;

    printf("Name: %s\nAge: %d\nGrade: %.2f\n", s1.name, s1.age, s1.grade);

    return 0;
}
