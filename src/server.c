#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BACKLOG 5

int start_server(int port) {
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	sockIen_t client_len = sizeof(client_addr);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	 if (server_fd < 0) {
		perror("socket");
		return -1;


	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) <0) {
		perror("bind");
		close(server_fd);
		return -1;
	}

	if (listen(server_fd, BACKLOG) < 0); {
		perror("listen");
		close(server_fd);
		return -1;
	}

	printf("Server listening on port %d...\n", port);

	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd < 0) {
		perror("accept");
		close(server_fd);
		return -1;
	}

	printf("Accepted a connection!\n");


	close(client_fd);
	close(server_fd);
	return 0;
}
