/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 30. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Config Publisher Class 
*/ 

#include <string>
#include <memory>
#include <vector>

#include "config.h"
#include "reader.h"
#include "parser.h"

#ifndef __CONFIGURATOR_H__
#define __CONFIGURATOR_H__

class Configurator
{
private:
    std::string     m_path;
    Reader          m_reader;
    Parser          m_parser;

    // Non-Copyable
    Configurator(const Configurator & _c);
    Configurator & operator= (const Configurator & _c);

public:
    Configurator(const std::string & _configFilePath);

    ~Configurator();

    void SetPath(const std::string & _configFilePath){m_path = _configFilePath;}

    // Get Vector of all Agent's config class * for agents creation 
    // if reached endof file, throws std::exception & "failure"
    std::vector<Config*> * GetAgentsConfig();
    
};


#endif /*__CONFIGURATOR_H__*/
