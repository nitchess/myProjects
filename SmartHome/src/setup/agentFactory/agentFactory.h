/** 
* @author			: Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate 	: 03. 06. 18
* @dateLastModified : 04. 06. 18
* @brief 			: Agent Factory Class 
*/ 

#ifndef __AGENT_FACTORY_H__
#define __AGENT_FACTORY_H__

#include <string>
#include <memory>

#include "agentFactory.h"
#include "iRegistrar.h"
#include "iPublisher.h"
#include "iAgent.h"
#include "config.h"


class AgentFactory
{
private:
	iPublisher * m_pub;
	iRegistrar * m_reg;

public:
	// CTOR
	AgentFactory(iPublisher * _pub, iRegistrar * _reg);
	// DTOR
	~AgentFactory();


	// Create agent fron dynamic library. 
	std::shared_ptr<iAgent> CreateDlAgent(const std::string & _dlPath, const std::string & _funcName, Config * _agentConfig);
	
	/*
	// Factory method - 
	// Flags:
	// 1 - Fire Sensor
	// 2 - Fire Controller
	// 3 - HVAC Sensor
	// 4 - HVAC Controller
	std::shared_ptr<iAgent> CreateAgent(Config * _agentConfig, unsigned int _flag);
	*/
};

#endif /*__AGENT_FACTORY_H__*/
