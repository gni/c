#include <stdio.h>
#include <string.h>

void parse_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        while (token) {
            printf("%s\t", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(file);
}

int main() {
    const char *filename = "example.csv";
    parse_csv(filename);
    return 0;
}
