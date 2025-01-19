#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;
    int ret;
    char *pattern = "^[a-zA-Z]+$";
    char *test_string = "HelloWorld";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    ret = regexec(&regex, test_string, 0, NULL, 0);
    if (!ret) {
        printf("Match\n");
    } else if (ret == REG_NOMATCH) {
        printf("No Match\n");
    } else {
        printf("Regex match error\n");
    }

    regfree(&regex);
    return 0;
}
