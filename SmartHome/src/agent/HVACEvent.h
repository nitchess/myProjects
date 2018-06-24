/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 05. 06. 18
* @brief            : HVAC Sensor Event class
*/ 

#ifndef __HEVENT_H__
#define __HEVENT_H__

#include <string>

#include "event.h"

class HVACEvent: public Event
{
private:
	double		m_temperature;

public:
	HVACEvent(const std::string & _type, const std::string & _building, const std::string & _floor, const std::string & _room,
	 double _payload);

	~HVACEvent();
	
	double GetPayload() const;
};


#endif /*__HEVENT_H__*/
