#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define CHUNK 16384

void compress_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    gzFile dest = gzopen(destination, "wb");

    if (!src || !dest) {
        fprintf(stderr, "Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[CHUNK];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK, src)) > 0) {
        gzwrite(dest, buffer, bytes_read);
    }

    fclose(src);
    gzclose(dest);
}

int main() {
    const char *source = "input.txt";
    const char *destination = "output.gz";

    compress_file(source, destination);
    printf("File compressed to %s\n", destination);
    return 0;
}
