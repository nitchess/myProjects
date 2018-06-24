/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 27. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Event ABC 
*/ 
#ifndef __EVENT_H__
#define __EVENT_H__

// #include <iostream>
#include <ctime>
// #include <memory>
// #include "location.h"

class Event
{
private:
    time_t                          m_timestamp;
    std::string                     m_type;
    std::string                     m_building;
    std::string                     m_floor;
    std::string                     m_room;

    // add const to all members
    // Non-Copyable
    Event(const Event & eve);
    Event & operator=(const Event & eve);

public:
    
    Event(const std::string & _type, const std::string & _building, const std::string & _floor, const std::string & _room):
     m_timestamp(time(0))
    {
        m_type = _type;
        m_building = _building;
        m_floor = _floor;
        m_room = _room;
    }

    virtual ~Event(){};
    
    // Getters
    const time_t                    GetTimestamp() const {return m_timestamp;}
    
    const std::string &             GetType() const {return m_type;}

    const std::string &             GetBuilding() const {return m_building;}

    const std::string &             GetFloor() const {return m_floor;}

    const std::string &             GetRoom() const {return m_room;}

};

#endif /*__EVENT_H__*/
