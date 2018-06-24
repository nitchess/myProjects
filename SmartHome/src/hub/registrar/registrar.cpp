/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 27. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Concrete Registrar implementation
*/ 

#include "registrar.h"

#include <algorithm>
#include <cassert>
#include <utility>

using namespace std;

// typedef std::multimap<std::string, iEventListener *>::iterator mm_itr;

Registrar::Registrar()
{
    // excep
    pthread_mutex_init(&m_regUnreg, NULL);
}

Registrar::~Registrar() 
{
    assert (pthread_mutex_destroy(&m_regUnreg) == 0);
}

void Registrar::Register(const std::string _evType, std::string _loc, iEventListener * _subscriber)
{
    pthread_mutex_lock(&m_regUnreg);

    // Insert new listener
    m_subscribers[_evType][_loc].push_back(_subscriber);

    pthread_mutex_unlock(&m_regUnreg);

    return;
}

void Registrar::Unregister(const std::string _type, std::string _loc, iEventListener * _subscriber)
{
    pthread_mutex_lock(&m_regUnreg);

    vector<iEventListener *>::iterator it;
    
    // what if location/event not exist
    it = find(m_subscribers[_type][_loc].begin(), m_subscribers[_type][_loc].end(), _subscriber);
    m_subscribers[_type][_loc].erase(it);

    pthread_mutex_unlock(&m_regUnreg);

    return;
}

// add locks
vector<iEventListener *> & Registrar::GetSubscribers(std::string _evType, std::string _loc)
{
    return m_subscribers[_evType][_loc];
}


/*
vector<iEventListener *> Registrar::GetSubscribers(std::string _evType, std::string _loc)
{
    vector<iEventListener *> resVec;

    mm_itr it = m_subscribers[_evType].begin();

    while (it != m_subscribers[_evType].end())
    {
        mm_itr itr = m_subscribers[_evType].find(_loc);

        if(itr != m_subscribers[_evType].end())
        {
            resVec.push_back(get<1>(*itr));
        }
        
        ++it;
    }

    return resVec;
}
*/
