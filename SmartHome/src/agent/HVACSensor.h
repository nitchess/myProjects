/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 30. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : HVAC Sensor Test 
*/ 

#ifndef __HVAC_SENSOR_H__
#define __HVAC_SENSOR_H__

#include <string>
#include <iostream>
#include <unistd.h>

#include "iPublisher.h"
#include "iAgent.h"
#include "HVACEvent.h"
#include "config.h"

class iRegistrar;

class HVACSensor: public iAgent
{
private:
    iPublisher *        m_pub;
    Config *            m_config;
    bool                m_runFlag;

    // Non-Copyable
    HVACSensor(const HVACSensor & _fs);   
    HVACSensor & operator=(const HVACSensor & _fs); 

public:
    HVACSensor(iPublisher * _pub, Config * _cnfg);

    ~HVACSensor();

    virtual void Run();

    virtual void Stop();

    // Getters
    virtual const std::string & GetID() const {return m_config->GetID();}
   
    virtual const std::string & GetType() const {return m_config->GetType();}

    virtual const std::string & GetBuilding() const {return m_config->GetBuilding();}

    virtual const std::string & GetRoom() const {return m_config->GetRoom();}

    virtual const std::string & GetFloor() const {return m_config->GetFloor();}

    virtual const std::string & GetLog() const {return m_config->GetLog();}

    virtual const std::string & GetConfig() const {return m_config->GetConfig();}

};


extern "C"
iAgent * HVACS_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg);

extern "C"
void * HVACSensorRun(void * _arg);

#endif /*__HVAC_SENSOR_H__*/
