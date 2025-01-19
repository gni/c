#include <stdio.h>
#include <stdint.h>

#define GPIO_BASE 0x3F200000
#define GPIO_SET *(volatile uint32_t *)(GPIO_BASE + 0x1C)
#define GPIO_CLR *(volatile uint32_t *)(GPIO_BASE + 0x28)

void set_gpio(int pin) {
    GPIO_SET = (1 << pin);
}

void clear_gpio(int pin) {
    GPIO_CLR = (1 << pin);
}

int main() {
    int pin = 17; // Example GPIO pin
    set_gpio(pin);
    printf("Pin %d set high.\n", pin);

    clear_gpio(pin);
    printf("Pin %d set low.\n", pin);

    return 0;
}
