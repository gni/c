#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void log_message(const char *level, const char *format, ...) {
    va_list args;
    va_start(args, format);

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove newline

    printf("[%s] [%s] ", time_str, level);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

int main() {
    log_message("INFO", "This is an informational message.");
    log_message("ERROR", "An error occurred: %s", "Invalid input");
    return 0;
}
