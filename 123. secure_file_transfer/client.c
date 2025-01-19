#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "encryption.h"

#define BUFFER_SIZE 1024

// Function to upload a file to the server
void upload_file(const char *filename, const char *server_ip, int port) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        fclose(file);
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        fclose(file);
        close(sock);
        exit(1);
    }

    printf("Connected to server at %s:%d\n", server_ip, port);

    // Send the file name
    send(sock, filename, strlen(filename) + 1, 0);

    // Read and send the file contents
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        xor_encrypt(buffer, bytes_read, "key123");
        send(sock, buffer, bytes_read, 0);
    }

    printf("File '%s' uploaded successfully.\n", filename);

    fclose(file);
    close(sock);
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <server_ip> <port>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *server_ip = argv[2];
    int port = atoi(argv[3]);

    upload_file(filename, server_ip, port);

    return 0;
}
