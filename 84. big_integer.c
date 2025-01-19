#include <stdio.h>
#include <string.h>

void add_large_numbers(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int carry = 0, i = 0;

    while (len1 > 0 || len2 > 0 || carry) {
        int sum = carry;
        if (len1 > 0) sum += num1[--len1] - '0';
        if (len2 > 0) sum += num2[--len2] - '0';
        result[i++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    result[i] = '\0';

    // Reverse the result
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

int main() {
    char num1[] = "123456789123456789";
    char num2[] = "987654321987654321";
    char result[50];

    add_large_numbers(num1, num2, result);
    printf("Sum: %s\n", result);
    return 0;
}
