#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "server.h"

#define PORT 8080
#define IP "127.0.0.1"

void acceptFunc(int _socket, const struct sockaddr_in * _addr)
{

	printf("Client %d Connected from port number: %d ip address: %s \n", _socket
    		, ntohs(_addr->sin_port), inet_ntoa(_addr->sin_addr));
	/*struct sockaddr_in sin;
	socklen_t len = sizeof(sin);

	if (getsockname(_socket, (struct sockaddr *)&sin, &len) == -1)
	{
    	perror("getsockname()");
	}
	else
	{
    	printf("Client %d Connected to port number: %d ip address: %s \n", _socket
    		, ntohs(sin.sin_port), inet_ntoa(sin.sin_addr));

	}*/
}

int readFunc(int _socket)
{
	sleep(1);
	srand((unsigned)(time(NULL)));

    // printf("Server Received packet to socket number: %d \n", _socket);

    return (rand() % 20);
}



void * serverThreadFunc(void * args)
{
    pthread_detach(pthread_self());

	run((TCPserver*)args, acceptFunc, readFunc);

	return args;
}



int main()
{
	pthread_t server;
	
	TCPserver * tcp = NULL;
	tcp = TCPserver_create(PORT);

	if(pthread_create(&server, NULL, serverThreadFunc, (void *)tcp) != 0)
	{
		perror("pthread_create() error");
	}


	pthread_join(server, NULL);

	return 0;
}


/*
int main()
{
	
	int i, n;

	TCPserver * tcp = NULL;
	tcp = TCPserver_create(PORT);

	run(tcp, acceptFunc, readFunc);

	return 0;
}
*/
