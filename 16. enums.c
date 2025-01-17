#include <stdio.h>

enum Days { MON, TUE, WED, THU, FRI, SAT, SUN };

int main() {
    enum Days today = FRI;

    if (today == FRI) {
        printf("It's Friday!\n");
    }

    return 0;
}
