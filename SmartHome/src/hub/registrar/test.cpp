#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>

#include "FireController.h"
#include "registrar.h"

using namespace std;

// FIRE CONFIG
string type =  "TestFire";
string building = "45";
string floor = "Galery";
string room = "room_1_a";
string log = "safety";
string sensConfig = "Fire_Detected; SIGUSER2";
string ctrlConfig = "On:Fire_Detected|Smoke_Detected; IoT: 10.10.3.42";

int main(int argc, char const *argv[])
{
	Registrar reg;
    FireController * test_listener;

    Config * frc = new Config("philips-sprinkler-1-a", type, building, floor, room, log, ctrlConfig);

    // Start producing
    int i = 10;
    while (i--)
    {
        test_listener = new FireController((iRegistrar*)(&reg), frc);
        reg.Register(test_listener->GetType(), test_listener->GetLocation(), test_listener);
    }

    vector<iEventListener *> & res = reg.GetSubscribers(type, test_listener->GetLocation());

    for (unsigned i = 0; i < res.size(); ++i)
    {
        cout << ' ' << res[i];
        cout << endl;
    }
    
    cout << endl;

    reg.Unregister(test_listener->GetType(), test_listener->GetLocation(), test_listener);

    for (unsigned i = 0; i < res.size(); ++i)
    {
        cout << ' ' << res[i];
        cout << '\n';
    }

	return 0;
}
