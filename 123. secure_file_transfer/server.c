#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "encryption.h"


#define BUFFER_SIZE 1024

void start_server(int port) {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_sock);
        exit(1);
    }

    if (listen(server_sock, 1) < 0) {
        perror("Error listening on socket");
        close(server_sock);
        exit(1);
    }

    printf("Server listening on port %d...\n", port);

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        perror("Error accepting connection");
        close(server_sock);
        exit(1);
    }

    printf("Client connected.\n");

    // Receive the file name
    char filename[BUFFER_SIZE];
    recv(client_sock, filename, sizeof(filename), 0);
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating file");
        close(client_sock);
        close(server_sock);
        exit(1);
    }

    // Receive and decrypt the file contents
    char buffer[BUFFER_SIZE];
    size_t bytes_received;
    while ((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        // Decrypt the data
        xor_encrypt(buffer, bytes_received, "key123");
        fwrite(buffer, 1, bytes_received, file);
    }

    printf("File '%s' received successfully.\n", filename);

    fclose(file);
    close(client_sock);
    close(server_sock);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    start_server(port);

    return 0;
}
