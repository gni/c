#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in6 server_addr;
    char *message = "Hello, Server!";
    char buffer[1024];

    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(8080);
    inet_pton(AF_INET6, "::1", &server_addr.sin6_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0);
    printf("Message sent: %s\n", message);

    recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    printf("Server response: %s\n", buffer);

    close(sockfd);
    return 0;
}
