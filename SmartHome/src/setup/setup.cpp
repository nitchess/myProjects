/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 05. 06. 18
* @dateLastModified : 07. 06. 18
* @brief            : Setup Class Implementation
*/
#include <iostream>
#include "setup.h"

// using namespace std;

Setup::Setup(const std::string _configPath, const std::string _soPath, iRegistrar * const _reg, 
    iPublisher * const _pub): m_reg(_reg), m_pub(_pub), m_cnfgPath(_configPath), m_soPath(_soPath),
    m_configurator(_configPath), m_af(m_pub, m_reg)
{

}

Setup::~Setup()
{

}

void Setup::SetPath(const std::string _configPath)
{
    m_cnfgPath = _configPath;
    m_configurator.SetPath(_configPath);

    return;
}

const std::string & Setup::GetPath()
{
    return m_cnfgPath;
}

   
vector<shared_ptr<iAgent> > * Setup::AgentsInit()
{
    vector<shared_ptr<iAgent> > * res = new vector<shared_ptr<iAgent> >;
    vector<Config*> * cVec = m_configurator.GetAgentsConfig();

    /*
    for (vector<Config*>::iterator i = cVec->begin(); i != cVec->end(); ++i)
    {
        cout << (*i)->GetID() << endl;
    }
    */

    for (vector<Config*>::iterator i = cVec->begin(); i != cVec->end(); ++i)
    {
        size_t pos = (*i)->GetID().find("_");
        // Convention For So FileName and func
        string usoName = (*i)->GetID().substr(0, pos); 

        cout << usoName << endl;
        res->push_back(m_af.CreateDlAgent( (m_soPath + "/" + usoName + ".so"), usoName + "_CreateAgent", *i));
    }

    delete cVec;

    return res;
}

