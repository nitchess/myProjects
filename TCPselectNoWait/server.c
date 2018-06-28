#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#include "server.h"

struct TCPserver
{
    struct sockaddr_in m_servAddr;
    fd_set m_set;
    int m_servAddrlen;
    int m_masterSocketFd;
    int m_sockestFd[1024];

    int m_fdFlag;
    int m_sendBytes;
    int m_readBytes;
    int m_optVal;
};

TCPserver * TCPserver_create(int _port)
{
    TCPserver * tcp = (TCPserver*)calloc(1, sizeof(TCPserver));
    tcp->m_servAddrlen = sizeof(tcp->m_servAddr);
    tcp->m_optVal = 1;

    if ((tcp->m_masterSocketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket() Failed \n");
        free(tcp);

        return NULL;
    }

     // make the server's socket's bound port fixed & reuse.
    if (setsockopt(tcp->m_masterSocketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &tcp->m_optVal, sizeof(tcp->m_optVal)))
    {
        perror("setsockopt() Failed");
        free(tcp);

        return NULL;
    }
    tcp->m_servAddr.sin_family = AF_INET;
    tcp->m_servAddr.sin_port = htons(_port);
    tcp->m_servAddr.sin_addr.s_addr = INADDR_ANY;

     // Forcefully attaching socket to the port 8080
    if (bind(tcp->m_masterSocketFd, (struct sockaddr *)&tcp->m_servAddr, sizeof(tcp->m_servAddr)) <0)
    {
        perror("bind() Failed");
        free(tcp);

        return NULL;
    }

    if (listen(tcp->m_masterSocketFd, 1000) < 0)
    {
        perror("liste() Failed \n");
        free(tcp);

        return NULL;
    }
    
    // Master socket = NOWAIT
    if (-1 == (tcp->m_fdFlag = fcntl(tcp->m_masterSocketFd, F_GETFL)))
    {
        perror("fcntl() Error");
         free(tcp);

        return NULL;
    }   
    if (-1 == fcntl(tcp->m_masterSocketFd, F_SETFL, tcp->m_fdFlag | O_NONBLOCK))
    {
        perror("fcntl() Error");
        free(tcp);

        return NULL;
    }

    return tcp;
}

void TCPserver_destroy(TCPserver ** _tcp)
{
    if (_tcp == NULL || *_tcp == NULL)
    {
        return;
    }
    close((*_tcp)->m_masterSocketFd);
    free(*_tcp);
    *_tcp = NULL;

    return;
}

static int TCPserver_accept(TCPserver * _tcp, fp2 _acceptFunc)
{
    errno = 0;
    int new_socket;

    new_socket = accept(_tcp->m_masterSocketFd, (struct sockaddr *)&_tcp->m_servAddr, (socklen_t*)&_tcp->m_servAddrlen);

    // if socket resource is allocated succesfuly
    // change Clients receive sockets to NO WAIT mode
    if (new_socket > 0 && errno != EAGAIN && errno != EWOULDBLOCK)
    {   
        _tcp->m_sockestFd[new_socket] = 1;
        // Accept Func
        (*(fp2)_acceptFunc)(new_socket,&_tcp->m_servAddr);

        if (-1 == (_tcp->m_fdFlag = fcntl(new_socket, F_GETFL)))
        {
            perror("fcntl() Error");
        }
        if (-1 == fcntl(new_socket, F_SETFL, _tcp->m_fdFlag | O_NONBLOCK))
        {
            perror("fcntl() Error");
        }
    }
  
    return new_socket;
}

static void TCPserver_close(TCPserver * _tcp, int _socketFd)
{
    _tcp->m_sockestFd[_socketFd] = 0;
    close(_socketFd);

    return;
}

static int TCPserver_sendTo(TCPserver * _tcp, int _socketFd, void* _msgToSend, size_t _bufferSize)
{
    
    _tcp->m_sendBytes = send(_socketFd, _msgToSend, _bufferSize, 0);
    if (_tcp->m_sendBytes < 0)
    {   
        perror("send() Failed");
    }
    

    return _tcp->m_sendBytes;   
}

static int TCPserver_receiveFrom(TCPserver * _tcp, int _socket, void* _msgToRec, size_t _bufferSize)
{
    errno = 0;
    _tcp->m_readBytes = read(_socket, _msgToRec, _bufferSize);

    // if real fail on receive, print error
    // else continue with no blocking
    if (errno != EAGAIN && errno != EWOULDBLOCK)
    {
        if (_tcp->m_readBytes == 0)
        {
            perror("Connection is closed");
        }
        else if (_tcp->m_readBytes < 0)
        {
            printf("recv() Failed: %d \n", _socket);
        }
    }

    return _tcp->m_readBytes;
}

void run(TCPserver * _tcp, fp2 _acceptFunc, fp _readFunc)
{

    int n, i, acceptFlag, activity, newSock, res;
    char buffer[LINE_MAX];
    char * msg = "Got Your MSG!";
    fd_set tempSet;
    
    if (_tcp == NULL || _acceptFunc == NULL || _readFunc == NULL)
    {
        return;
    }

    // Clear the fd Set
    FD_ZERO(&_tcp->m_set);
    // Add master socket to set
    FD_SET(_tcp->m_masterSocketFd, &_tcp->m_set);
    

    while (1)
    {
        tempSet = _tcp->m_set;

        // Get the number of ready fd (aka sockets)
        if ((activity = select(1024, &tempSet, NULL, NULL, NULL)) < 0 && errno == EINTR) 
        {
            perror("select() error");
            return;
        }

        // Add Child sockets to the set
        if (FD_ISSET(_tcp->m_masterSocketFd, &tempSet)) 
        {
            acceptFlag = 1;
            while (acceptFlag) 
            {
                newSock = TCPserver_accept(_tcp, _acceptFunc);

                if (newSock < 0)
                {
                    acceptFlag = 0;
                }
                else
                {
                    FD_SET(newSock, &_tcp->m_set);
                }
            }
            // took care of server master socket
            --activity;       
        }
        
        for (i = 0; i < 1024 && activity; ++i)
        {
            if(_tcp->m_sockestFd[i] && FD_ISSET(i, &tempSet))
            {
                n = TCPserver_receiveFrom(_tcp, i, buffer, LINE_MAX);
                if (n > 0)
                {
                    // buffer[n] = '\0';
                    res = (*(fp)_readFunc)(i);
                    TCPserver_sendTo(_tcp, i, &res, sizeof(int));    
                }
                else if (n == 0)
                {
                    TCPserver_close(_tcp, i);
                    FD_CLR(i, &_tcp->m_set);

                    printf("UNREGISTER socket %d\n", i);
                }

                // Took care of on child socket
                --activity;
            }
        }
    }

    return;
}

// 1. callback option
// accept func() - after creating socket in the server -> belong to the app not to the client
// read func()   - after receiving from the  client-> callback to app function
// optianal "stopflag func"
// void run(accept func, readfunc) - on a thread

// 2. return value to the app
// int run(void * buffer, int length)
// return and run from server

