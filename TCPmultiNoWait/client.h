/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 24. 06. 18
* @dateLastModified : 24. 06. 18
* @brief            : TCP Client Header
*/ 
#ifndef __TCLIENT_H__
#define __TCLIENT_H__

#include <stddef.h>

typedef struct TCPclient TCPclient;

TCPclient * TCPclient_create(int _port, const char * _ip);
void		TCPclient_destroy(TCPclient ** _tcp);

int TCPclient_sendTo(TCPclient * _tcp, void* _msgToSend, size_t _bufferSize);
int TCPclient_receiveFrom(TCPclient * _tcp, void* _msgToRec, size_t _bufferSize);

#endif /*__TCLIENT_H__*/
