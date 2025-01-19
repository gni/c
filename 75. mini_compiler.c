#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile(const char *expression) {
    printf(".section .data\n");
    printf(".section .text\n");
    printf(".global _start\n");
    printf("_start:\n");

    const char *ptr = expression;
    while (*ptr) {
        if (*ptr >= '0' && *ptr <= '9') {
            printf("    mov $%c, %%eax\n", *ptr);
        } else if (*ptr == '+') {
            printf("    add %%ebx, %%eax\n");
        } else if (*ptr == '-') {
            printf("    sub %%ebx, %%eax\n");
        }
        ptr++;
    }
    printf("    mov $1, %%eax\n");
    printf("    int $0x80\n");
}

int main() {
    const char *expression = "2+3-1";
    compile(expression);
    return 0;
}
