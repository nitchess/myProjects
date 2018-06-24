#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <memory> 

#include "setup.h"
#include "agentFactory.h"
#include "hub.h"
#include "iAgent.h"
#include "config.h"


using namespace std;

void * ThreadRunFunc(void * _arg)
{
	iAgent * agent = static_cast<iAgent *>(_arg);

	agent->Run();

	return 0;
}


int main()
{
	pthread_t t_id[2];
    void* status;

    vector<shared_ptr<iAgent> > * agents;

    Hub* hub = new Hub;
    hub->Run();

    Setup st( "./config.INI", "./soFiles",(iRegistrar*)(hub->GetRegistrar()), ((iPublisher*)hub->GetPublisher()) );

    agents = st.AgentsInit();

    size_t j = 0;
    for (std::vector<shared_ptr<iAgent> >::iterator i = agents->begin(); i != agents->end(); ++i)
    {
    	cout << (*i)->GetID() << endl;

		pthread_create(&t_id[j], 0, ThreadRunFunc, (i)->get());
		++j;
    }
    
     // Run HVAC sensor & ctrl
    // pthread_create(&t_id[1], 0, HVACCtrlRun, &(*hc));

    sleep(30);

    for (std::vector<shared_ptr<iAgent> >::iterator i = agents->begin(); i != agents->end(); ++i)
    {
    	(*i)->Stop();
    }

    for (int i = 0; i < 2; ++i)
    {
        pthread_join(t_id[i], &status);
        // agents.push_back(static_cast<iAgent*>(status));
    }	
	
	return 0;
}
