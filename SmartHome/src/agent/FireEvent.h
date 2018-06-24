/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 03. 06. 18
* @brief            : Fire Sensor Event class
*/ 

#ifndef __FEVENT_H__
#define __FEVENT_H__

#include <string>
#include "event.h"

class Location;

class FEvent: public Event
{
private:
	std::string		m_payload;

public:
	FEvent(const std::string & _type, const std::string & _building, const std::string & _floor, const std::string & _room,
	 const std::string & _payload);

	~FEvent();
	
	const std::string & GetPayload() const;
};


#endif /*__FEVENT_H__*/
