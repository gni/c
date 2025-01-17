#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {0}, client = {0};
    char buffer[1024];

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    socklen_t len = sizeof(client);
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &len);
    printf("Received: %s\n", buffer);

    sendto(sock, "Hello, Client!", 14, 0, (struct sockaddr *)&client, len);
    close(sock);
    return 0;
}
