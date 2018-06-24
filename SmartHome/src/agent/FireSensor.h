/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 30. 05. 18
* @brief            : Fire Sensor Test 
*/ 

#ifndef __FIRE_SENSOR_H__
#define __FIRE_SENSOR_H__

#include <string>
#include <iostream>
#include <unistd.h>

#include "iPublisher.h"
#include "iAgent.h"
#include "FireEvent.h"
#include "config.h"

class iRegistrar;

class FireSensor: public iAgent
{
private:
    iPublisher *        m_pub;
    Config *            m_config;
    std::string         m_payload;
    bool                m_runFlag;

    // Non-Copyable
    FireSensor(const FireSensor & _fs);   
    FireSensor & operator=(const FireSensor & _fs); 

public:
    FireSensor(iPublisher * _pub, Config * _cnfg);

    ~FireSensor();

    virtual void Run();

    virtual void Stop();

    // Getters
    virtual const std::string & GetID() const {return m_config->GetID();}
   
    virtual const std::string & GetType() const {return m_config->GetType();}

    virtual const std::string & GetBuilding() const {return m_config->GetBuilding();}

    virtual const std::string & GetFloor() const {return m_config->GetFloor();}

    virtual const std::string & GetRoom() const {return m_config->GetRoom();}

    virtual const std::string & GetLog() const {return m_config->GetLog();}

    virtual const std::string & GetConfig() const {return m_config->GetConfig();}

};

extern "C"
iAgent * FS_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg);

extern "C"
void * FireSensorRun(void * _arg);

#endif /*__FIRE_SENSOR_H__*/
