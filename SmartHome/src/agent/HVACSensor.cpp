/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 03. 06. 18
* @brief            : HVAC Sensor implementation 
*/ 

#include "HVACSensor.h"

using namespace std;

HVACSensor::HVACSensor(iPublisher * _pub, Config * _cnfg): m_pub(_pub)
{
    // Init from config
    m_config = _cnfg;
    m_runFlag = true;
}

HVACSensor::~HVACSensor() 
{
    delete m_config;
}

void HVACSensor::Run()
{
    double temperature = 24.50;

    while(m_runFlag)
    {
        sleep(2);

        std::shared_ptr<Event> newEvent(new HVACEvent(m_config->GetLog(),  m_config->GetBuilding(),
         m_config->GetFloor(), m_config->GetRoom(), temperature));
        
        m_pub->PushEvent(newEvent);
        cout << "Sent Temperature Event\n";

        ++temperature;
    }

    return;
}

void HVACSensor::Stop()
{
    m_runFlag = false;

    return;
}

extern "C"
iAgent * HVACS_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg)
{
    return (new HVACSensor(_pub, _cnfg));
}

extern "C"
void * HVACSensorRun(void * _arg)
{
    HVACSensor * hs = static_cast<HVACSensor *>(_arg);

    hs->Run();

    return 0;
}

