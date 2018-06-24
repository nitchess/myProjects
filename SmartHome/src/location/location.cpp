/** 
* @author			: Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate 	: 04. 06. 18
* @dateLastModified : 04. 06. 18
* @brief 			: Location Classes Implementations 
*/

#include "location.h"

using namespace std;

// 
Building::Building(string _bldng)
{
	m_description = _bldng + ",";
}

Building::~Building()
{

}

const std::string Building::GetDescription() const
{
	return m_description;
}

// 
Decorator::Decorator(std::shared_ptr<Location> _lctn)
{
	m_location = _lctn;
}

Decorator::~Decorator()
{

}

const std::string Decorator::GetDescription() const
{
	return  m_location->GetDescription();
}

// 
Floor::Floor(std::string _floor, std::shared_ptr<Location> _bldng):Decorator(_bldng)
{
	m_description =  _floor + ",";
}

Floor::~Floor()
{

}

const std::string Floor::GetDescription() const
{
	string res = Decorator::GetDescription(); 

	return (res += m_description);
}

// 
Room::Room(std::string _room, std::shared_ptr<Location> _floor):Decorator(_floor)
{
	m_description = _room + ",";
}

Room::~Room()
{

}

const std::string Room::GetDescription() const
{
	string res = Decorator::GetDescription(); 

	return (res += m_description);
}
