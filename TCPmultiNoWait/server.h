/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 24. 06. 18
* @dateLastModified : 26. 06. 18
* @brief            : TCP Client Header
*/ 
#ifndef __TSERVER_H__
#define __TSERVER_H__

#include <stddef.h>

typedef struct TCPserver TCPserver;

TCPserver * TCPserver_create(int _port);
void		TCPserver_destroy(TCPserver ** _tcp);

void run(TCPserver * _tcp, void * _acceptFunc, void* _readFunc);

void run1(TCPserver * _tcp, void * _buffer, size_t _size);

#endif /*__TSERVER_H__*/
