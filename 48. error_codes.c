#include <stdio.h>

typedef enum {
    SUCCESS = 0,
    ERR_FILE_NOT_FOUND = 1,
    ERR_MEMORY_ALLOCATION = 2,
} ErrorCode;

void handle_error(ErrorCode code) {
    switch (code) {
        case SUCCESS:
            printf("Operation successful.\n");
            break;
        case ERR_FILE_NOT_FOUND:
            printf("Error: File not found.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("Error: Memory allocation failed.\n");
            break;
    }
}

int main() {
    handle_error(ERR_FILE_NOT_FOUND);
    return 0;
}
