#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192

void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    if (!src) {
        perror("Error opening source file");
        exit(1);
    }

    FILE *dest = fopen(destination, "wb");
    if (!dest) {
        perror("Error opening destination file");
        fclose(src);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;

    while ((bytes = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    copy_file(argv[1], argv[2]);
    return 0;
}
