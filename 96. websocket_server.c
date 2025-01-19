#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <stdint.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void generate_websocket_accept_key(const char *client_key, char *accept_key) {
    const char *guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char concatenated[BUFFER_SIZE];
    snprintf(concatenated, sizeof(concatenated), "%s%s", client_key, guid);

    unsigned char sha1_hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)concatenated, strlen(concatenated), sha1_hash);

    size_t output_len = 0;
    char *base64_hash = (char *)malloc(BUFFER_SIZE);
    EVP_EncodeBlock((unsigned char *)base64_hash, sha1_hash, SHA_DIGEST_LENGTH);

    strncpy(accept_key, base64_hash, BUFFER_SIZE);
    free(base64_hash);
}

void handle_websocket_connection(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char *client_key_start = strstr(buffer, "Sec-WebSocket-Key: ");
    if (client_key_start) {
        char client_key[256];
        sscanf(client_key_start, "Sec-WebSocket-Key: %s", client_key);

        char accept_key[BUFFER_SIZE];
        generate_websocket_accept_key(client_key, accept_key);

        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response),
                 "HTTP/1.1 101 Switching Protocols\r\n"
                 "Upgrade: websocket\r\n"
                 "Connection: Upgrade\r\n"
                 "Sec-WebSocket-Accept: %s\r\n\r\n",
                 accept_key);
        send(client_socket, response, strlen(response), 0);

        printf("WebSocket handshake completed.\n");
        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            int bytes_read = read(client_socket, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) break;

            printf("Received: %s\n", buffer);
            send(client_socket, buffer, bytes_read, 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("WebSocket server listening on port %d...\n", PORT);
    while (1) {
        int client_socket = accept(server_fd, NULL, NULL);
        handle_websocket_connection(client_socket);
    }

    return 0;
}
