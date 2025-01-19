#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void process_packet(unsigned char *buffer, int size) {
    struct iphdr *ip_header = (struct iphdr *)buffer;
    printf("Packet: Source: %s, Dest: %s\n",
           inet_ntoa(*(struct in_addr *)&ip_header->saddr),
           inet_ntoa(*(struct in_addr *)&ip_header->daddr));
}

int main() {
    int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (raw_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    unsigned char *buffer = malloc(65536);
    while (1) {
        int data_size = recvfrom(raw_socket, buffer, 65536, 0, NULL, NULL);
        if (data_size < 0) {
            perror("recvfrom failed");
            break;
        }
        process_packet(buffer, data_size);
    }

    close(raw_socket);
    free(buffer);
    return 0;
}
