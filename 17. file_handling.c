#include <stdio.h>

int main() {
    FILE *fptr;

    // Write to a file
    fptr = fopen("example.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fptr, "Hello, file handling in C!\n");
    fclose(fptr);

    // Read from a file
    fptr = fopen("example.txt", "r");
    char line[100];
    while (fgets(line, sizeof(line), fptr)) {
        printf("%s", line);
    }
    fclose(fptr);

    return 0;
}
