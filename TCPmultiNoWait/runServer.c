#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

#include "server.h"

#define PORT 8080
#define IP "127.0.0.1"

int main()
{
	
	int i, n;

	TCPserver * tcp = NULL;
	tcp = TCPserver_create(PORT);

	run(tcp, NULL, NULL);

	return 0;
}

/*
int main()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAXLINE] = {0};
    char* hello = "OK";
    
    memset(&address, 0, sizeof(address));
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
	if (listen(server_fd, 50) < 0) {
	    perror("listen");
	    exit(EXIT_FAILURE);
	}
	
	int flags;
	
	if (-1 == (flags = fcntl(server_fd, F_GETFL))) {
		perror("error at fcntl. F_GETFL.");
		exit(EXIT_FAILURE);
	}
	
	if (-1 == fcntl(server_fd, F_SETFL, flags | O_NONBLOCK)) {
		perror("error at fcntl. F_SETFL.");
		exit(EXIT_FAILURE);
	}
	
	int i, socks[1024] = {0};
    while (1) 
    {
		errno = 0;
    	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*) &addrlen);
    	
		if (errno != EAGAIN && errno != EWOULDBLOCK && new_socket >= 0) {
			socks[new_socket] = 1;
			printf("SOCKET CREATED\n");
			if (-1 == (flags = fcntl(new_socket, F_GETFL))) {
				perror("error at fcntl. F_GETFL.");
				exit(EXIT_FAILURE);
			}
			if (-1 == fcntl(new_socket, F_SETFL, flags | O_NONBLOCK)) {
				perror("error at fcntl. F_SETFL.");
				exit(EXIT_FAILURE);
			}
		}
		
		for (i = 0; i < 1024; ++i) {
			if (socks[i]) {
				valread = read(i, buffer, MAXLINE);
				if (valread > 0) {
					buffer[valread] = '\0';
					printf("%d %s\n", valread, buffer);
					send(i, hello, strlen(hello), 0);
				} else if (valread == 0) {
					socks[i] = 0;
					close(i);
				}
			}
		}
	}
	
    return 0;
}
	*/
