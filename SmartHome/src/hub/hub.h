/** 
* @author			: Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate 	: 28. 05. 18
* @dateLastModified : 28. 05. 18
* @brief 			: HUB Class 
*/ 

#ifndef __HUB_H__
#define __HUB_H__

#include <pthread.h>
#include <memory>

class Distributer;
class Registrar;
class Publisher;

class Hub
{
private:
	Publisher 	*	m_pub;
	Registrar   *	m_reg;
	Distributer *   m_dis;
	pthread_t		m_disThread;

	// Non-Copyable
	Hub(const Hub & _hub);
	Hub & operator=(const Hub & _hub);

public:
	// CTOR
	Hub();
	// DTOR
	~Hub();

	// Run Function
	void Run();

	// Getters
	const Publisher * GetPublisher() {return m_pub;}
	const Registrar * GetRegistrar() {return m_reg;}
	
};

#endif /*__HUB_H__*/
