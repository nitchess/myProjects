/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 27. 05. 18
* @dateLastModified : 29. 05. 18
* @brief            : Concrete Publisher 
*/ 
#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

#include "iPublisher.h"
#include "waitableQueue.h"

#include <memory>

class Event;

class Publisher: public iPublisher
{
private:
    WaitableQueue<std::shared_ptr<Event> > *  m_eventsQueue;

    // Non-Copyable
    Publisher(const Publisher & _pub);
    Publisher & operator=(const Publisher & _pub);

public:
    Publisher();

    virtual ~Publisher();
    
    virtual void PushEvent(std::shared_ptr<Event>  _newEvent);
    
    virtual std::shared_ptr<Event> PopEvent(); 

};
    
#endif /*__PUBLISHER_H__*/
