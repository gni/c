#include <stdio.h>
#include <string.h>

void parse_config(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char key[50], value[50];
        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            printf("Key: %s, Value: %s\n", key, value);
        }
    }

    fclose(file);
}

int main() {
    parse_config("config.ini");
    return 0;
}
