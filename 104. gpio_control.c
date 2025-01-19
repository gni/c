#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"
#define GPIO_DIRECTION "/sys/class/gpio/gpio%d/direction"
#define GPIO_VALUE "/sys/class/gpio/gpio%d/value"

void write_to_file(const char *path, const char *value) {
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }
    write(fd, value, strlen(value));
    close(fd);
}

void gpio_setup(int pin, const char *direction) {
    char path[128];
    char pin_str[8];
    sprintf(pin_str, "%d", pin);

    // Export GPIO pin
    write_to_file(GPIO_EXPORT, pin_str);

    // Set direction
    sprintf(path, GPIO_DIRECTION, pin);
    write_to_file(path, direction);
}

void gpio_write(int pin, int value) {
    char path[128];
    char value_str[2];
    sprintf(path, GPIO_VALUE, pin);
    sprintf(value_str, "%d", value);

    write_to_file(path, value_str);
}

void gpio_cleanup(int pin) {
    char pin_str[8];
    sprintf(pin_str, "%d", pin);
    write_to_file(GPIO_UNEXPORT, pin_str);
}

int main() {
    int pin = 17; // GPIO pin 17
    gpio_setup(pin, "out");

    for (int i = 0; i < 10; i++) {
        gpio_write(pin, 1); // Turn LED on
        sleep(1);
        gpio_write(pin, 0); // Turn LED off
        sleep(1);
    }

    gpio_cleanup(pin);
    return 0;
}
