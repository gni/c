#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 8192
#define LISTEN_PORT 8080
#define FORWARD_HOST "23.215.0.138" // example.com
#define FORWARD_PORT 80

void forward_data(int source_fd, int dest_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes;
    while ((bytes = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        write(dest_fd, buffer, bytes);
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr = {0}, client_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(LISTEN_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    printf("Proxy server listening on port %d...\n", LISTEN_PORT);

    while (1) {
        socklen_t addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        int forward_fd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in forward_addr = {0};
        forward_addr.sin_family = AF_INET;
        forward_addr.sin_port = htons(FORWARD_PORT);
        inet_pton(AF_INET, FORWARD_HOST, &forward_addr.sin_addr);

        connect(forward_fd, (struct sockaddr *)&forward_addr, sizeof(forward_addr));

        if (fork() == 0) {
            forward_data(client_fd, forward_fd);
            forward_data(forward_fd, client_fd);
            close(client_fd);
            close(forward_fd);
            exit(0);
        }

        close(client_fd);
        close(forward_fd);
    }

    return 0;
}
