/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 03. 06. 18
* @brief            : Fire Sensor Event 
*/ 

#include "FireEvent.h"

using namespace std;

FEvent::FEvent(const std::string & _type, const std::string & _building, const std::string & _floor,
 const std::string & _room, const std::string & _payload):Event(_type, _building, _floor, _room)
{
	m_payload = _payload;
}

FEvent::~FEvent()
{

}
	
const std::string & FEvent::GetPayload() const
{
	return m_payload;
}
