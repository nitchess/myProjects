/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 03. 06. 18
* @brief            : Fire Sensor Implementation
*/ 

#include "FireSensor.h"

using namespace std;

FireSensor::FireSensor(iPublisher * _pub, Config * _cnfg): m_pub(_pub)
{
    // Init from config
    m_config = _cnfg;
    m_runFlag = true;
    m_payload = "No_Fire_Detected";
}

FireSensor::~FireSensor() 
{
    delete m_config;
}

void FireSensor::Run()
{

    while(m_runFlag)
    {
        sleep(2);

        std::shared_ptr<Event> newEvent(new FEvent(m_config->GetLog(), m_config->GetBuilding(), m_config->GetFloor(),
         m_config->GetRoom(), m_payload));

        m_pub->PushEvent(newEvent);
        cout << "Sent Fire Event\n";
        m_payload = "Fire_Detected; SIGUSER2";
        
    }

    return;
}

void FireSensor::Stop()
{
    m_runFlag = false;

    return;
}

extern "C"
iAgent * FS_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg)
{
    return (new FireSensor(_pub, _cnfg));
}

extern "C"
void * FireSensorRun(void * _arg)
{
    FireSensor * fs = static_cast<FireSensor *>(_arg);

    fs->Run();

    return 0;
}

