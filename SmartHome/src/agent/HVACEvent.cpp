/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 03. 06. 18
* @brief            : HVAC Sensor Event 
*/ 

#include "HVACEvent.h"

using namespace std;

HVACEvent::HVACEvent(const std::string & _type, const std::string & _building, const std::string & _floor, const std::string & _room,
 double _payload):Event(_type, _building, _floor, _room)
{
	m_temperature = _payload;
}

HVACEvent::~HVACEvent()
{

}
	
double HVACEvent::GetPayload() const
{
	return m_temperature;
}
