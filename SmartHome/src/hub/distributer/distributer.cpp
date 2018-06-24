/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 29. 05. 18
* @brief            : HUB's Distributer Class implementation 
*/ 

#include "distributer.h"
#include "publisher.h"
#include "registrar.h"
#include "iEventListener.h"
#include "event.h"

#include <string>
#include <memory>

using namespace std;

Distributer::Distributer(iPublisher * _pub, iRegistrar * _reg)
{
    m_publisher = _pub;
    m_reg = static_cast<Registrar*>(_reg);
}

Distributer::~Distributer(){}

void Distributer::Distributer::Run()
{
    shared_ptr<Event> tEvent;

    while (true)
    {
        // Get Event from Queue
        tEvent = m_publisher->PopEvent();

        // Insert to SQL
        
        // registerar logics!
        
        // Get all building listeners
        vector<iEventListener *> res = m_reg->GetSubscribers(tEvent->GetType(), tEvent->GetBuilding());

        // Get all floor listeners
        vector<iEventListener *> & fl = m_reg->GetSubscribers(tEvent->GetType(), (tEvent->GetBuilding() + tEvent->GetFloor()));
        res.insert(res.end(), fl.begin(), fl.end());
        
        // Get subscribers for room listeners
        vector<iEventListener *> & rl = m_reg->GetSubscribers(tEvent->GetType(), (tEvent->GetBuilding() + tEvent->GetFloor()
            + tEvent->GetRoom()));
        res.insert(res.end(), rl.begin(), rl.end());

        // Notify all relevant subscribers
        for (vector<iEventListener *>::iterator i = res.begin(); i != res.end(); ++i)
        {
            (*i)->Notify(tEvent);
        }
    }

    return;
}

extern "C"
void * DistributerRun(void * _arg)
{
    Distributer * ds = static_cast<Distributer *>(_arg);

    ds->Run();

    return 0;
}
