/** 
* @author			: Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate 	: 27. 05. 18
* @dateLastModified : 27. 05. 18
* @brief 			: iRegistrar Interface Class 
*/ 
#ifndef __IREGISTRAR_H__
#define __IREGISTRAR_H__

#include <string>

class iEventListener;
class Location;

class iRegistrar
{
	
public:
	
	virtual void Register(const std::string _evType, const std::string _loc, iEventListener * _subscriber) = 0;

	virtual void Unregister(const std::string _evType, const std::string _loc, iEventListener * _subscriber) = 0;

};


#endif /*__IREGISTRAR_H__
*/
