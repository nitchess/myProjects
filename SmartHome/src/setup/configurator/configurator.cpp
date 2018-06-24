/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 05. 06. 18
* @dateLastModified : 05. 06. 18
* @brief            : Config Publisher Implementation 
*/ 

#include "configurator.h"

using namespace std;

Configurator::Configurator(const std::string & _configFilePath): m_path(_configFilePath)
{

}

Configurator::~Configurator()
{

}

std::vector<Config*> * Configurator::GetAgentsConfig()
{
	int cnfgLinesNum = 7;
	std::string line;
	vector<Config*> * res = new vector<Config*>;

	m_reader.Open(m_path);

	while (m_reader.isGood())
	{
		vector<string> v;

		// Read & Parse Single Config Block
		for (int i = 0; i < cnfgLinesNum; ++i)
		{
			m_reader.ReadLine(line);
			m_parser.ParseLine(line);
			v.push_back(line);
		}

		// Skip empty line
		m_reader.ReadLine(line);

		// Create Config From vector
		Config * newCnfg = new Config(v);
		res->push_back(newCnfg);
	}

	m_reader.Close();

	return res;
}
