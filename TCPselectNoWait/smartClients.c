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
#define CLIENTS 1000

#define PORT 8080
#define IP "127.0.0.1"

int main()
{
	TCPclient * clients[CLIENTS] = {0};
	char msg[LINE_MAX] = "From Client";
    char buffer[LINE_MAX] = {0};
    int res;
    int i, readB = 0, sendB = 0;


	srand((unsigned)(time(NULL)));
  	
  	while (1) 
  	{
	  	for (i = 0; i < CLIENTS; ++i) 
	  	{
	  		// Connect 40% of clients
			if (!clients[i] && (rand() % 20 < 8)) 
			{
				clients[i] = TCPclient_create(PORT, IP);
				if (!clients[i])
				{
					puts("Client init error");
				}
			}
			// Disconnect 20% of connected clients
			else if (clients[i] && (rand() % 20 < 1)) 
			{
 				TCPclient_destroy(&clients[i]);
 				clients[i] = 0;
			}
			
			// only 70% of the connected clients sends msg
			if (clients[i] && (rand() % 100 < 70)) 
			{
				sendB = TCPclient_sendTo(clients[i], msg, strlen(msg));
				assert(sendB);
				readB = TCPclient_receiveFrom(clients[i], &res, sizeof(int));
				assert(readB);
				// buffer[readB] = '\0';
				printf("Server: %d\n", res);
			}
		}
	}
	
	return 0;
}

