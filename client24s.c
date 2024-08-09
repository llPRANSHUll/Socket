#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9070 // Change from 8080 to 9090


void communicate_with_server(int sock) {
    char buffer[1024] = {0};
    char command[1024];

    while (1) {
        printf("Enter command: ");
        fgets(command, 1024, stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character
        send(sock, command, strlen(command), 0);

        if (strcmp(command, "exit") == 0) {
            break;
        }

        int valread = read(sock, buffer, 1024);
        buffer[valread] = '\0';
        printf("Server response: %s\n", buffer);
    }
}

int main() {
    struct sockaddr_in address;
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    communicate_with_server(sock);
    close(sock);
    return 0;
}
