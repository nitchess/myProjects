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

#include "server.h"

struct TCPserver
{
    struct sockaddr_in m_servAddr;
    int m_servAddrlen;
    int m_masterSocketFd;
    int m_fdFlag;
    int m_sockestFd[1024];
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

    if (listen(tcp->m_masterSocketFd, 256) < 0)
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

static void TCPserver_register(TCPserver * _tcp, void * _acceptFunc)
{
    errno = 0;
    int new_socket;

    new_socket = accept(_tcp->m_masterSocketFd, (struct sockaddr *)&_tcp->m_servAddr, (socklen_t*)&_tcp->m_servAddrlen);

    // Clients rec sockets - NO WAIT
    if (errno != EAGAIN && errno != EWOULDBLOCK && new_socket > 0)
    {   
        _tcp->m_sockestFd[new_socket] = 1;

        if (-1 == (_tcp->m_fdFlag = fcntl(new_socket, F_GETFL)))
        {
            perror("fcntl() Error");

            return;
        }
        if (-1 == fcntl(new_socket, F_SETFL, _tcp->m_fdFlag | O_NONBLOCK))
        {
            perror("fcntl() Error");

            return;
        }
        printf("SOCKET CREATED\n"); 
    }

    //_acceptFunc(socketFd, ip, port);
    
    return;
}

static void TCPserver_unregister(TCPserver * _tcp, int _socketFd)
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

void run1(TCPserver * _tcp, void * _buffer, size_t _size)
{
    int n, i;
    char buffer[LINE_MAX];
    char * msg = "Got Your MSG!";

    if (_tcp == NULL)
    {
        return;
    }

    while (1)
    {
        TCPserver_register(_tcp, _acceptFunc);
        
        for (i = 0; i < 1024; ++i)
        {
            if(_tcp->m_sockestFd[i])
            {
                n = TCPserver_receiveFrom(_tcp, i, buffer, LINE_MAX);
                if (n > 0)
                {
                    buffer[n] = '\0';
                    printf("Received Message %d %s\n", n, buffer);

                    // _readFunc()
                    TCPserver_sendTo(_tcp, i, msg, strlen(msg));    
                }
                else if (n == 0)
                {
                    TCPserver_unregister(_tcp, i);
                    printf("UNREGISTER\n");
                }
            }
        }
    }

    return;
}

void run(TCPserver * _tcp, void * _acceptFunc, void* _readFunc)
{
    int n, i;
    char buffer[LINE_MAX];
    char * msg = "Got Your MSG!";

    if (_tcp == NULL)
    {
        return;
    }

    while (1)
    {
        TCPserver_register(_tcp, _acceptFunc);
        
        for (i = 0; i < 1024; ++i)
        {
            if(_tcp->m_sockestFd[i])
            {
                n = TCPserver_receiveFrom(_tcp, i, buffer, LINE_MAX);
                if (n > 0)
                {
                    buffer[n] = '\0';
                    printf("Received Message %d %s\n", n, buffer);

                    // _readFunc()
                    TCPserver_sendTo(_tcp, i, msg, strlen(msg));    
                }
                else if (n == 0)
                {
                    TCPserver_unregister(_tcp, i);
                    printf("UNREGISTER\n");
                }
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


/*    
    int i, socks[1024] = {0};
    
    while (1) {
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
                        
                } else if (valread == 0) {
                    socks[i] = 0;
                    close(i);
                }
            }
        }
    }
    
    return 0;*/


/*
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int i, opt = 1, flags;
    int addrlen = sizeof(address);
    char buffer[1021] = {0};
    char *hello = "Hello from server";
    int sockets[1021] = {0};
    int sock;  
      
     memset(&address, 0, sizeof(address));
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
      
    if (bind(server_fd, (struct sockaddr *)&address,  sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    
    if (-1 == (flags = fcntl(server_fd, F_GETFL)))
    {
        perror("error at fcntl");
        exit(EXIT_FAILURE);
    }
    
        
    if (-1 == fcntl(server_fd, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            sockets[new_socket] = 1;
            sock = new_socket;
            if (-1 == (flags = fcntl(server_fd, F_GETFL)))
            {
                perror("error at fcntl");
                exit(EXIT_FAILURE);
            }
                
            if (-1 == fcntl(server_fd, F_SETFL, flags | O_NONBLOCK))
            {
                perror("error at fcntl");
                exit(EXIT_FAILURE);
            }
            printf("SOCKET CREATED");
            
        }
        
        for (i=0; i<1024; ++i)
        {
            if (sockets[i])
            {
                valread = read(i , buffer, 1024);
                if (valread > 0)
                {
                    buffer[valread] = '\0';
                    printf("%d %s \n", valread, buffer);
                    send(i , hello , strlen(hello) , 0);
                }
            }
        }
        errno=0;
    }
    return 0;
}
*/
