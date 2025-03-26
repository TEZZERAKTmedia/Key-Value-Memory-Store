#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BACKLOG 5

int start_server(int port) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[2048];
    socklen_t addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen)) >= 0) {
        printf("Accepted a connection!\n");

        int valread;
        while ((valread = read(client_fd, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[valread] = '\0';
            printf("Received: %s\n", buffer);

            // Echo back or process commands here
            write(client_fd, "OK\n", 3);
        }

        close(client_fd);
    }

    return 0;
}
