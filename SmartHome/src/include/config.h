/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 30. 05. 18
* @dateLastModified : 30. 05. 18
* @brief            : iAgent's Config ABC 
*/ 
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <iostream>
#include <vector>

class Config
{
private:
	std::string         m_id;
    std::string         m_type;

    std::string			m_building;
    std::string         m_floor;
    std::string         m_room;

    std::string         m_log;
    std::string         m_config;

    //  Non-Copyable
    Config(const Config & _cnfg);
    Config & operator=(const Config & _cnfg);

public:
	// CTOR
	Config(std::string _id, std::string _type, std::string _building, std::string _floor, std::string _room,
		std::string _log, std::string _config)
	{
		m_id = _id;
		m_type = _type;
		m_building = _building;
		m_floor = _floor;
		m_room = _room;
		m_log = _log;
		m_config = _config;
	}

	Config(std::vector<std::string> & _vec)
	{
		m_id = _vec[0];
		m_type = _vec[1];
		m_building = _vec[2];
		m_floor = _vec[3];
		m_room = _vec[4];
		m_log = _vec[5];
		m_config = _vec[6];
	}	

	// DTOR
	virtual ~Config(){}

	// Getters
	virtual const std::string & GetID() const {return m_id;}
   
    virtual const std::string & GetType() const {return m_type;}

    virtual const std::string & GetBuilding() const {return m_building;}

    virtual const std::string & GetFloor() const {return m_floor;}

    virtual const std::string & GetRoom() const {return m_room;}

    virtual const std::string & GetLog() const {return m_log;}

    virtual const std::string & GetConfig() const {return m_config;}
	
};


/*
using namespace std;
// UNIT_TEST
ostream& operator <<(ostream& os, const Config& _cnfg)
{
	os << _cnfg.GetID() << endl;
	os << _cnfg.GetType() << endl;
	os << _cnfg.GetRoom() << endl;
	os << _cnfg.GetFloor() << endl;
	os << _cnfg.GetLog() << endl;
	os << _cnfg.GetConfig() << endl;

	return os;	
}
*/

#endif /*__CONFIG_H__*/
