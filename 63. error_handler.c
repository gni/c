#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS = 0,
    ERR_FILE_NOT_FOUND,
    ERR_MEMORY_ALLOCATION,
    ERR_INVALID_INPUT
} ErrorCode;

const char *get_error_message(ErrorCode code) {
    switch (code) {
        case SUCCESS: return "Success";
        case ERR_FILE_NOT_FOUND: return "File not found";
        case ERR_MEMORY_ALLOCATION: return "Memory allocation failed";
        case ERR_INVALID_INPUT: return "Invalid input";
        default: return "Unknown error";
    }
}

void handle_error(ErrorCode code) {
    if (code != SUCCESS) {
        fprintf(stderr, "Error: %s\n", get_error_message(code));
        exit(code);
    }
}

int main() {
    ErrorCode code = ERR_FILE_NOT_FOUND;
    handle_error(code); // This will terminate the program with an error message.
    return 0;
}
