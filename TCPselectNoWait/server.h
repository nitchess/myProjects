/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 24. 06. 18
* @dateLastModified : 26. 06. 18
* @brief            : TCP Client Header
*/ 
#ifndef __TSERVER_H__
#define __TSERVER_H__

#include <stddef.h>
#include <netinet/in.h>

typedef int (*fp)(int _socket);
typedef void (*fp2)(int _socket, const struct sockaddr_in * _addr);

typedef struct TCPserver TCPserver;

TCPserver * TCPserver_create(int _port);
void		TCPserver_destroy(TCPserver ** _tcp);

void run(TCPserver * _tcp, fp2 _acceptFunc, fp _readFunc);

#endif /*__TSERVER_H__*/
