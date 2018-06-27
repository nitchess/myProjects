/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 24. 06. 18
* @dateLastModified : 24. 06. 18
* @brief            : TCP Client Implementation
*/
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include "client.h"

struct TCPclient
{
    struct sockaddr_in m_servAddr;
    int m_socketFd;
    int m_serverSocket;
    int m_sendBytes;
    int m_readBytes;
};

TCPclient * TCPclient_create(int _port, const char * _ip)
{
	TCPclient * tcp = (TCPclient*)calloc(1, sizeof(TCPclient));

	if (_ip == NULL)
	{
		return NULL;
	}
	
	if ((tcp->m_socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket() Failed \n");
        free(tcp);

        return NULL;
    }

    tcp->m_servAddr.sin_family = AF_INET;
    tcp->m_servAddr.sin_port = htons(_port);
    tcp->m_servAddr.sin_addr.s_addr = inet_addr(_ip);

    if (connect(tcp->m_socketFd, (struct sockaddr *)&tcp->m_servAddr, sizeof(tcp->m_servAddr)) < 0)
    {
        perror("Connection Failed \n");
        free(tcp);

        return NULL;
    }

    return tcp;
}

void TCPclient_destroy(TCPclient ** _tcp)
{
	if (_tcp == NULL || *_tcp == NULL)
	{
		return;
	}
	close((*_tcp)->m_socketFd);
	free(*_tcp);
	*_tcp = NULL;

	return;
}

int TCPclient_sendTo(TCPclient * _tcp, void* _msgToSend, size_t _bufferSize)
{
	if (_tcp == NULL || _msgToSend == NULL)
	{
		return 0;
	}

	_tcp->m_sendBytes = send(_tcp->m_socketFd , _msgToSend, _bufferSize, 0);
	if (_tcp->m_sendBytes < 0)
	{	
		perror("send() Failed");	
	}

   return _tcp->m_sendBytes;
}

int TCPclient_receiveFrom(TCPclient * _tcp, void* _msgToRec, size_t _bufferSize)
{
	if (_tcp == NULL)
	{
		return 0;
	}

	_tcp->m_readBytes = read(_tcp->m_socketFd, _msgToRec, _bufferSize);
	if (_tcp->m_readBytes == 0)
	{
		perror("Connection is closed");
		return _tcp->m_readBytes;
	}
	else if (_tcp->m_readBytes < 0)
	{
		perror("recv() Failed");
		return _tcp->m_readBytes;
	}

	return _tcp->m_readBytes;
}
