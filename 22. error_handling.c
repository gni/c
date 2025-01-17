#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *fptr = fopen("nonexistent.txt", "r");

    if (fptr == NULL) {
        printf("Error opening file: %s\n", strerror(errno));
        return 1;
    }

    fclose(fptr);
    return 0;
}
