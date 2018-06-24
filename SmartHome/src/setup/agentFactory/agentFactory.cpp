/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 04. 06. 18
* @dateLastModified : 04. 06. 18
* @brief            : Agent Factory Class Implementation 
*/ 

#include <dlfcn.h>
#include <string>
#include <pthread.h>
#include <unistd.h>

#include "agentFactory.h"
// #include "FireController.h"
// #include "FireSensor.h"
// #include "HVACController.h"
// #include "HVACSensor.h"

using namespace std;

typedef iAgent * (*f_ptr)(iRegistrar *, iPublisher *, Config *);

AgentFactory::AgentFactory(iPublisher * _pub, iRegistrar * _reg): m_pub(_pub), m_reg(_reg)
{
    
}

AgentFactory::~AgentFactory()
{

}


std::shared_ptr<iAgent> AgentFactory::CreateDlAgent(const string & _dlPath, const string & _funcName, Config * _agentConfig)
{
    void * handle = NULL;
    f_ptr functionPtr = NULL;

    handle = dlopen(_dlPath.c_str(), RTLD_LAZY);
    if (!handle) 
    {
       // throw(){}
    }

    functionPtr = (f_ptr)( dlsym(handle, _funcName.c_str()) );
    if (!functionPtr) 
    {
       // throw(){}
    }

    return ( shared_ptr<iAgent>( (functionPtr)(m_reg, m_pub, _agentConfig)) );
}


/*
std::shared_ptr<iAgent> AgentFactory::CreateAgent(Config * _agentConfig, unsigned int _flag)
{
    if (_flag == 1)
    {
        return shared_ptr<iAgent>(new FireSensor(m_pub, _agentConfig));
    }
    else if (_flag == 2)
    {
        return shared_ptr<iAgent>(new FireController(m_reg, _agentConfig)); 
    }
    else if (_flag == 3)
    {
        return shared_ptr<iAgent>(new HVACSensor(m_pub, _agentConfig));
    }
    else
    {
        return shared_ptr<iAgent>(new HVACController(m_reg, _agentConfig));
    }

    return NULL;
}
*/
