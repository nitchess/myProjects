/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Agent interface Class 
*/ 

#ifndef __IAGENT_H__
#define __IAGENT_H__

#include <string>
// #include <memory>
// #include "location.h"

class iAgent
{

public:

	// Run Function - While Loop Sending Events
    virtual void Run() = 0;
    
    // Stop Function
    virtual void Stop() = 0;

    // Getters
    virtual const std::string & GetID() const = 0;
   
    virtual const std::string & GetType() const = 0;

    virtual const std::string & GetBuilding() const = 0;

    virtual const std::string & GetFloor() const = 0;

    virtual const std::string & GetRoom() const = 0;

    virtual const std::string & GetLog() const = 0;

    virtual const std::string & GetConfig() const = 0;

};


#endif /*__IAGENT_H__*/
