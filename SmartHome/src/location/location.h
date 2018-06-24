/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 04. 06. 18
* @dateLastModified : 04. 06. 18
* @brief            : Location Classes 
*/ 

#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>
#include <memory>

// Interface Class - lowest denominator
class Location
{
public:
    virtual const std::string GetDescription() const = 0;
};

// Core Class
class Building: public Location 
{
private:
    std::string     m_description;

    // Non-Copyable
    Building(const Building & _bldng);
    Building & operator= (const Building & _bldng);

public:
    // 
    Building(std::string _bldng);
    // 
    virtual ~Building();

    virtual const std::string GetDescription() const;
};

// Decorator Class
class Decorator: public Location
{
private:
    std::shared_ptr<Location>  m_location;

public:
    // 
    Decorator(std::shared_ptr<Location>  _lctn);
    // 
    virtual ~Decorator();
    
    // 
    virtual const std::string GetDescription() const;
};

 
// Optional Classes
// 
class Floor: public Decorator
{
private:
    std::string     m_description;

    // Non-Copyable
    Floor(const Floor & _flr);
    Floor & operator= (const Floor & _flr);

public:
    Floor(std::string _floor, std::shared_ptr<Location> _lctn);
    ~Floor();

    virtual const std::string GetDescription() const;
}; 

// 
class Room: public Decorator
{
private: 
    std::string     m_description;

    // Non-Copyable
    Room(const Room & _rm);
    Room & operator= (const Room & _rm);

public:

    Room( std::string _room, std::shared_ptr<Location> _lctn);
    ~Room();

    virtual const std::string GetDescription() const;
};

#endif /*__LOCATION_H__*/
