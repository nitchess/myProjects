/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 03. 06. 18
* @brief            : HVAC Controller Implementation 
*/ 

#include "HVACController.h"

using namespace std;

HVACController::HVACController(iRegistrar * _reg, Config * _cnfg): m_reg(_reg)
{
    // private func - init from config object
    m_config = _cnfg;
    m_regLocation = m_config->GetBuilding() + m_config->GetFloor() + m_config->GetRoom();
    m_runFlag = true;
    m_payload = 0.0;
}

HVACController::~HVACController() 
{
    m_reg->Unregister(m_config->GetLog(), m_regLocation, this);

    delete m_config;
}

void HVACController::Run()
{
    m_reg->Register(m_config->GetLog(), m_regLocation, this);

    while (m_runFlag)
    {
        cout << "HVAC Ctrl current Payload\n" << m_payload << endl;
        sleep(2);
    }

    return;
}

void HVACController::Stop()
{
    m_runFlag = false;

    return;
}

void HVACController::Notify(std::shared_ptr<Event> & _event)
{
    cout << "Received Temperature Event: " << _event->GetBuilding() << ", " << _event->GetFloor() << ", " << _event->GetRoom() << endl;

    shared_ptr<HVACEvent> event1 = dynamic_pointer_cast<HVACEvent>(_event); 
    m_payload = event1->GetPayload();
}   

extern "C"
iAgent * HVACC_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg)
{
    return (new HVACController(_reg, _cnfg));
}

extern "C"
void * HVACCtrlRun(void * _arg)
{
    HVACController * hc = static_cast<HVACController *>(_arg);

    // std::cout << "run\n";
    hc->Run();

    return 0;
}
