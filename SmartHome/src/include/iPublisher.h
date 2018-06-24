/** 
* @author			: Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate 	: 27. 05. 18
* @dateLastModified : 28. 05. 18
* @brief 			: iPublisher Interface Class 
*/ 
#ifndef __iPUBLISHER_H__
#define __iPUBLISHER_H__

#include <memory>

class Event;

class iPublisher
{

public:
	
	virtual void PushEvent(std::shared_ptr<Event> _newEvent) = 0;

	virtual std::shared_ptr<Event> PopEvent() = 0;

};

#endif /*__PUBLISHER_H__*/
