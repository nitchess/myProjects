/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 07. 06. 18
* @dateLastModified : 07. 06. 18
* @brief            : Setup Class
*/

#ifndef __SETUP_H__
#define __SETUP_H__

#include <string>
#include <vector>
#include <memory>
#include "configurator.h"
#include "agentFactory.h"

class iRegistrar;
class iPublisher;
class Config;


class Setup
{
private:
    iRegistrar *    m_reg;
    iPublisher *    m_pub;
    std::string     m_cnfgPath;
    std::string     m_soPath;
    Configurator    m_configurator;
    AgentFactory    m_af;

    // Non-Copyable
    Setup(const Setup & _set);
    Setup & operator=(const Setup & _set);

public:
    // CTOR
    Setup(const std::string _configPath, const std::string _soPath, iRegistrar * const _reg, iPublisher * const _pub);
    // DTOR
    ~Setup();

    // Change config file
    inline void SetPath(const std::string _configPath);
    inline const std::string & GetPath();

    // Change .so path
    inline void SetSoPath(const std::string _soPath){m_soPath = _soPath;}

    // Agents initialization
    std::vector<std::shared_ptr<iAgent> > * AgentsInit();
};

#endif /*__SETUP_H__*/
