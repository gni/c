#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

int main() {
    struct Student s1 = { "Alice", 20, 3.9 };
    struct Student s2;

    // Write to binary file
    FILE *fptr = fopen("student.dat", "wb");
    if (!fptr) {
        printf("Error opening file!\n");
        return 1;
    }
    fwrite(&s1, sizeof(struct Student), 1, fptr);
    fclose(fptr);

    // Read from binary file
    fptr = fopen("student.dat", "rb");
    fread(&s2, sizeof(struct Student), 1, fptr);
    fclose(fptr);

    printf("Name: %s, Age: %d, Grade: %.2f\n", s2.name, s2.age, s2.grade);
    return 0;
}
