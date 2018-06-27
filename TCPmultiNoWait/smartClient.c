#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <assert.h>
#include <limits.h>

#include "client.h"
#include "server.h"

#define MAXLINE 1024
#define CLIENTS 1003

#define PORT 8080
#define IP "127.0.0.1"

int main()
{
	TCPclient * tcp = NULL;
	char msg[LINE_MAX] = "From Client";
    char buffer[LINE_MAX] = {0};
    int readB = 0;
    int sendB = 0;

	tcp = TCPclient_create(PORT, IP);

	if (!tcp)
	{
		return -1;
	}

	sendB = TCPclient_sendTo(tcp, msg, strlen(msg));
	assert(sendB);
	readB = TCPclient_receiveFrom(tcp, buffer, LINE_MAX);
	assert(readB);
	buffer[readB] = '\0';
	printf("Server: %s\n", buffer);

	TCPclient_destroy(&tcp);
	
	return 0;
}





/* 
int main() {
    struct sockaddr_in address;
    int flags, i, sock[CLIENTS] = {0}, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAXLINE] = {0};
    char msg[MAXLINE] = "Client message";
    
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    char addr[64];
    int port;
    printf("Enter server IP and Port: ");
    scanf("%s %d", addr, &port);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    
    if(inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    srand((unsigned)(time(NULL)));
  	
  	while (1) {
	  	for (i = 0; i < CLIENTS; ++i) {
			if (!sock[i] && (rand() % 20 < 8)) {
				sock[i] = socket(AF_INET, SOCK_STREAM, 0);
				if (connect(sock[i], (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
					printf("\nConnection Failed \n");
					sock[i] = 0;
					//return -1;
				}
			} else if (sock[i] && (rand() % 20 < 1)) {
				close(sock[i]);
				sock[i] = 0;
			}
			
			if (sock[i] && (rand() % 20 < 14)) {
				send(sock[i], msg, strlen(msg), 0);
				valread = read(sock[i], buffer, MAXLINE);
				buffer[valread] = '\0';
				printf("Server: %s\n", buffer);
			}
		}
	}
    
    return 0;
}
*/
