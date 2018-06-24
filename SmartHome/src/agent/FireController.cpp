/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 05. 06. 18
* @brief            : Fire Controller Implementation
*/ 
#include "FireController.h"

using namespace std;

// typedef shared_ptr<Location> s_ptr;

FireController::FireController(iRegistrar * _reg, Config * _cnfg): m_reg(_reg)
{
    // private func - init from config object
    m_config = _cnfg;
    m_regLocation = m_config->GetBuilding();
    m_runFlag = true;
    m_payload = "No_Fire_Detected";
}

FireController::~FireController() 
{
    m_reg->Unregister(m_config->GetLog(), m_regLocation, this);

    delete m_config;
}

void FireController::Run()
{
    m_reg->Register(m_config->GetLog(), m_regLocation, this);

    while (m_runFlag)
    {
        cout << "Fire Ctrl current Payload\n" << m_payload << endl;
        sleep(2);
    }

    return;
}

void FireController::Stop()
{
    m_runFlag = false;

    return;
}

void FireController::Notify(std::shared_ptr<Event> & _event)
{
    cout << "Received Fire Event:" << _event->GetBuilding() << ", " << _event->GetFloor() << ", " << _event->GetRoom() << endl;
    m_payload = dynamic_pointer_cast<FEvent>(_event)->GetPayload();
}   


extern "C"
void * FireCtrlRun(void * _arg)
{
    FireController * fc = static_cast<FireController *>(_arg);

    // std::cout << "run\n";
    fc->Run();

    return 0;
}

extern "C"
iAgent * FC_CreateAgent(iRegistrar * _reg, iPublisher * _pub, Config * _cnfg)
{
    return (new FireController(_reg, _cnfg));
}

