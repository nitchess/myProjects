/** 
* @author			: Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate 	: 27. 05. 18
* @dateLastModified : 28. 05. 18
* @brief 			: Event Listener API 
*/ 
#ifndef __IEVENTLISTENER_H__
#define __IEVENTLISTENER_H__

#include <memory>

class Event;

class iEventListener
{

public:
	
	// Notify the subscriber 
	virtual void Notify(std::shared_ptr<Event> & _event) = 0;	
};

#endif /*__IEVENTLISTENER_H__*/
