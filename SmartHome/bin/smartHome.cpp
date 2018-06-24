/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 09. 06. 18
* @dateLastModified : 09. 06. 18
* @brief            : Smart Home Main executable
*/ 

#include <iostream>
#include <exception>
#include <memory>
#include <vector>
#include <limits.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#include "hub.h"
#include "setup.h"
#include "iAgent.h"

using namespace std;

void * ThreadRunFunc(void * _arg)
{
    iAgent * agent = static_cast<iAgent *>(_arg);

    agent->Run();

    return 0;
}

int main()
{
    void* status;
    int cont = 1;           // trigger to stop loop 
    unsigned int option;

    Hub * hub = new Hub;
    hub->Run();
    Setup * st = 0;

    vector<shared_ptr<iAgent> > * initRes;

    vector<shared_ptr<iAgent> > agents;
    vector<pthread_t> t_id;

    try
    {
        while (cont)
        {
            cout << "Choose option:" << endl;
            cout << "   1: Add Devices From Config File" << endl;
            cout << "   2: Run Agents" << endl;
            cout << "   3: Pause" << endl;
            cout << "   4: Resume" << endl;
            cout << "   5: Stop Agents" << endl;

            cout << "   Any other number - exit " << endl;

            cin >> option;
            system("clear");
            system("echo ∆ Hello Hub User ∆");
            switch(option)
            {
                case 1:
                {
                    char * cPath = new char[PATH_MAX];
                    char * soPath = new char[PATH_MAX];

                    cout << "Plz enter Config file Path: ";
                    cin >> cPath;
                    cout << endl;

                    cout << "Plz enter .so files Path: ";
                    cin >> soPath;
                    cout << endl;

                    st = new Setup(cPath, soPath, (iRegistrar*)(hub->GetRegistrar()), 
                        ((iPublisher*)hub->GetPublisher()));

                    initRes = st->AgentsInit();
                    agents.insert(agents.end(), initRes->begin(), initRes->end());
                    delete initRes;    

                    delete[] cPath;
                    delete[] soPath;

                    break;
                }

                case 2:
                {
                    size_t j = t_id.size(); // initialy will be 0
                    t_id.resize(t_id.size() + agents.size()); // to add agents

                    for (vector<shared_ptr<iAgent> >::iterator i = agents.begin(); i != agents.end(); ++i)
                    {
                        cout << (*i)->GetID() << endl;

                        pthread_create(&t_id[j], 0, ThreadRunFunc, (i)->get());
                        ++j;
                    }

                    break;
                }

                case 3:
                {
                    
                    break;
                }

                case 4:
                {

                    break;
                }

                case 5:
                {
                    for (vector<shared_ptr<iAgent> >::iterator i = agents.begin(); i != agents.end(); ++i)
                    {
                        (*i)->Stop();
                    }

                    break;
                }

                default: cont = 0;  
                         break;
            }
            
        }
    }
    catch(...)
    {
        cout << "exception cought" << endl;
    }

    for (size_t i = 0; i < t_id.size(); ++i)
    {
        pthread_join(t_id[i], &status);
    }

    return 0;
}
