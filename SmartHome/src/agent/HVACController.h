/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 30. 05. 18
* @dateLastModified : 04. 06. 18
* @brief            : HVAC Controller Test 
*/ 

#ifndef __HVAC_CTRL_H__
#define __HVAC_CTRL_H__

#include <string>
#include <iostream>
#include <unistd.h>

#include "iEventListener.h"
#include "iAgent.h"
#include "iRegistrar.h"
#include "config.h"
#include "HVACEvent.h"

class iPublisher;

class HVACController: public iAgent ,public iEventListener
{
private:
    iRegistrar *        m_reg;
    Config *            m_config;
    std::string         m_regLocation;
    double              m_payload;
    bool                m_runFlag;

    // Non-Copyable
    HVACController(const HVACController & _fc);
    HVACController & operator=(const HVACController & _fc);

public:
    HVACController(iRegistrar * _reg, Config * _cnfg);

    virtual ~HVACController();

    virtual void Run();

    virtual void Stop();

    virtual void Notify(std::shared_ptr<Event> & _event);   

    virtual const std::string & GetID() const {return m_config->GetID();}
   
    virtual const std::string & GetType() const {return m_config->GetType();}

    virtual const std::string & GetBuilding() const {return m_config->GetBuilding();}

    virtual const std::string & GetFloor() const {return m_config->GetFloor();}

    virtual const std::string & GetRoom() const {return m_config->GetRoom();}

    virtual const std::string & GetLog() const {return m_config->GetLog();}

    virtual const std::string & GetConfig() const {return m_config->GetConfig();}

};

extern "C"
iAgent * HVACC_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg);

extern "C"
void * HVACCtrlRun(void * _arg);

#endif /*__HVAC_CTRL_H__*/
