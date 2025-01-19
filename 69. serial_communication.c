#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int serial_fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        perror("Error opening serial port");
        return 1;
    }

    struct termios tty;
    tcgetattr(serial_fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tcsetattr(serial_fd, TCSANOW, &tty);

    char *message = "Hello, Serial!";
    write(serial_fd, message, strlen(message));
    close(serial_fd);
    return 0;
}
