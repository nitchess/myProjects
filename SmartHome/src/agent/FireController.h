/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Fire Controller Test 
*/ 

#ifndef __FIRE_CTRL_H__
#define __FIRE_CTRL_H__

#include <string>
#include <iostream>
#include <unistd.h>
// #include <memory>
#include "iRegistrar.h"
#include "iEventListener.h"
#include "iAgent.h"
#include "config.h"
// #include "location.h"
#include "FireEvent.h"

class iPublisher;

class FireController: public iAgent ,public iEventListener
{
private:
    iRegistrar *                 m_reg;
    Config *                     m_config;
    std::string                  m_regLocation;
    std::string                  m_payload;
    bool                         m_runFlag;

    // Non-Copyable
    FireController(const FireController & _fc);
    FireController & operator=(const FireController & _fc);

public:
    FireController(iRegistrar * _reg, Config * _cnfg);

    virtual ~FireController();

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
iAgent * FC_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg);

extern "C"
void * FireCtrlRun(void * _arg);

#endif /*__FIRE_CTRL_H__*/
