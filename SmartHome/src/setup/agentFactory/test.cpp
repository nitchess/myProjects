#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <memory>

#include "agentFactory.h"
#include "hub.h"
#include "HVACSensor.h"
#include "HVACController.h"
#include "iAgent.h"
#include "config.h"

using namespace std;

// FIRE CONFIG
string type =  "TestFire";
string building = "45";
string floor = "Galery";
string room = "room_1_a";
string log = "safety";
string sensConfig = "Fire_Detected; SIGUSER2";
string ctrlConfig = "On:Fire_Detected|Smoke_Detected; IoT: 10.10.3.42";

// HVAC CONFIG
string Htype =  "TestHVAC";
string Hroom = "room_1_a";
string Hfloor = "Galery";
string Hlog = "hvac_log";
string HsensConfig = "units: F; lower: -5; upper:55; period: 12";
string HctrlConfig = "iot:10.10.1.64; tmp:77; shutdown: Fire_Detected|ROOM_EMPTY";

/*
void * ctrlA(void* args)
{
    Config * frc = new Config("philips-fireCtrl", type, room, floor, log, ctrlConfig);

    // cout << "Controller config: " << *frc;

    iRegistrar* reg = static_cast<iRegistrar*>(args);

    iAgent * fc = FC_CreateAgent(reg, NULL, frc);
    fc->Run();

    pthread_exit(fc);

}

void * sensA(void* args)
{
    Config * frs = new Config("philips-fireCtrl", type, room, floor, log, sensConfig);

    // cout << "Sensor config: " << *frs;

    iPublisher* pub = static_cast<iPublisher*>(args);

    string id = "philips-fireSensor";

    iAgent * fs = FS_CreateAgent(NULL, pub, frs);
    fs->Run();

    pthread_exit(fs);
}
*/

int main()
{
    pthread_t t_id[2];

    vector<shared_ptr<iAgent> > agents;
    void* status;

    Hub* hub = new Hub;
    hub->Run();

    // FIRE CONFIG
    // Config * frs = new Config("philips-fireSensor-1-a", type, building, floor, room, log, sensConfig);
    // Config * frc = new Config("philips-sprinkler-1-a", type, building, floor, room, log, ctrlConfig);

    // HVAC CONFIG
    Config * hvs = new Config("electra-hvac-sensor-1", Htype, building, Hfloor, Hroom, Hlog, HsensConfig);
    Config * hvc = new Config("electra-hvac-ctrl-1", Htype, building, Hfloor, Hroom, Hlog, HctrlConfig);

    AgentFactory af((iPublisher*)hub->GetPublisher(), (iRegistrar*)(hub->GetRegistrar()));

    // Create HVAC sensor & controller
    shared_ptr<iAgent> hc = af.CreateDlAgent("../soFiles/HVAC.so", "HVACC_CreateAgent", hvc); 
    agents.push_back(hc);


    shared_ptr<iAgent> hs = af.CreateDlAgent("../soFiles/HVACS.so", "HVACS_CreateAgent", hvs); 
    agents.push_back(hs);

    // shared_ptr<iAgent> hs ( HVACS_CreateAgent((iRegistrar*)(hub->GetRegistrar()), (iPublisher*)hub->GetPublisher(), hvs) );
    // agents.push_back(hs);

    // Run HVAC sensor & ctrl
    pthread_create(&t_id[0], 0, HVACSensorRun, &(*hs));
    pthread_create(&t_id[1], 0, HVACCtrlRun, &(*hc));

    sleep(30);

    agents[0]->Stop();
    agents[1]->Stop();

    for (int i = 0; i < 2; ++i)
    {
        pthread_join(t_id[i], &status);
        // agents.push_back(static_cast<iAgent*>(status));
    }

    return 0;
}
