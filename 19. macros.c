#include <stdio.h>

#define PI 3.14159
#define AREA_OF_CIRCLE(r) (PI * (r) * (r))

int main() {
    float radius = 5.0;
    printf("Area of the circle: %.2f\n", AREA_OF_CIRCLE(radius));
    return 0;
}
