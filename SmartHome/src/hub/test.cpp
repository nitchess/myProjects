#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "hub.h"
#include "event.h"
#include "FireSensor.h"
#include "FireController.h"
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
    pthread_t t_id[4];

    vector<iAgent*> agents;
    void* status;

    Hub* hub = new Hub;
    hub->Run();

    // FIRE CONFIG
    Config * frs = new Config("philips-fireSensor-1-a", type, building, floor, room, log, sensConfig);
    Config * frc = new Config("philips-sprinkler-1-a", type, building, floor, room, log, ctrlConfig);

    // HVAC CONFIG
    Config * hvs = new Config("electra-hvac-sensor-1", Htype, building, Hfloor, Hroom, Hlog, HsensConfig);
    Config * hvc = new Config("electra-hvac-ctrl-1", Htype, building, Hfloor, Hroom, Hlog, HctrlConfig);


    // Create fire sensor & ctrl
    iAgent * fs = FS_CreateAgent((iRegistrar*)(hub->GetRegistrar()), (iPublisher*)hub->GetPublisher(), frs);
    agents.push_back(fs);
    iAgent * fc = FC_CreateAgent((iRegistrar*)(hub->GetRegistrar()), (iPublisher*)hub->GetPublisher(), frc);
    agents.push_back(fc);

    // Create HVAC sensor & controller
    iAgent * hs = HVACS_CreateAgent((iRegistrar*)(hub->GetRegistrar()), (iPublisher*)hub->GetPublisher(), hvs);
    agents.push_back(hs);
    iAgent * hc = HVACC_CreateAgent((iRegistrar*)(hub->GetRegistrar()), (iPublisher*)hub->GetPublisher(), hvc);
    agents.push_back(hc);

    // Run fire sensor & ctrl
    pthread_create(&t_id[0], 0, FireCtrlRun, fc);
    pthread_create(&t_id[1], 0, FireSensorRun, fs);

    // Run HVAC sensor & ctrl
    pthread_create(&t_id[2], 0, HVACSensorRun, hc);
    pthread_create(&t_id[3], 0, HVACCtrlRun, hs);


    sleep(15);

    agents[0]->Stop();
    agents[1]->Stop();
    agents[2]->Stop();
    agents[3]->Stop();
    
    /*
    pthread_create(&t_id[0], 0, ctrlA, (void*)hub->GetRegistrar());
    pthread_create(&t_id[1], 0, sensA, (void*)hub->GetPublisher());
    */

    for (int i = 0; i < 4; ++i)
    {
        pthread_join(t_id[i], &status);
        // agents.push_back(static_cast<iAgent*>(status));
    }

    return 0;
}
