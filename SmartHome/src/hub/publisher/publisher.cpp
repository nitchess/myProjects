/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 29. 05. 18
* @brief            : Publisher 
*/ 

#include "publisher.h"

Publisher::Publisher()
{
    // throw std::exception
    m_eventsQueue = new WaitableQueue<std::shared_ptr<Event> >;
}

Publisher::~Publisher()
{
    delete m_eventsQueue;
}

void Publisher::PushEvent(std::shared_ptr<Event> _newEvent)
{
    m_eventsQueue->Push(_newEvent);

    return;
}

std::shared_ptr<Event> Publisher::PopEvent()
{
    return m_eventsQueue->Pop();
}
