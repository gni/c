#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Waiting for a connection...\n");
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    printf("Connection established!\n");

    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Received: %s\n", buffer);

    close(client_fd);
    close(server_fd);
    return 0;
}
