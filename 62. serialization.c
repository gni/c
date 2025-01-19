#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float score;
} Student;

void save_to_file(const char *filename, Student *student) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fwrite(student, sizeof(Student), 1, file);
    fclose(file);
}

void load_from_file(const char *filename, Student *student) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fread(student, sizeof(Student), 1, file);
    fclose(file);
}

int main() {
    Student s1 = {1, "Alice", 95.5};
    save_to_file("student.dat", &s1);

    Student s2;
    load_from_file("student.dat", &s2);
    printf("Loaded Student: ID=%d, Name=%s, Score=%.2f\n", s2.id, s2.name, s2.score);

    return 0;
}
