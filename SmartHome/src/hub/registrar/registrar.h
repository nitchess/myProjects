/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 27. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Concrete Registrar 
*/ 
#ifndef __REGISTRAR_H__
#define __REGISTRAR_H__

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <pthread.h>

// #include "location.h"
#include "iRegistrar.h"

class iEventListener;

class Registrar: public iRegistrar
{

private:

	// Members
    // std::map<const std::string, std::multimap<std::shared_ptr<Location>, 
            // iEventListener *, cmpLocation > >  m_subscribers;

	std::map<const std::string, std::map<const std::string, std::vector<iEventListener *> > > m_subscribers; 

    // std::map<const std::string, std::multimap<std::string, iEventListener *> > m_subscribers;  	
    pthread_mutex_t     m_regUnreg;

    // Non-Copyable
    Registrar(const Registrar & _reg);
    Registrar & operator=(const Registrar & _reg);

public:
    Registrar();

    virtual ~Registrar();
    
    virtual void Register(const std::string _evType, std::string _loc, iEventListener * _subscriber);

    virtual void Unregister(const std::string _evType, std::string _loc, iEventListener * _subscriber);

    std::vector<iEventListener *> & GetSubscribers(const std::string _evType, const std::string _loc);

};


    /*
public:
    // Comparison Struct
    struct cmpLocation 
    {
        bool operator()(const std::string & _a, const std::string & _b) const 
        {
            // if _a's string size is larger
            if (_a.compare(0, _b.size(), _b) < 0)
            {
                return true;
            }
            else if(_a.compare(0, _a.size(), _b) < 0)
            {
                return true;
            }

            return false;
        }
    };
    */
#endif /*__REGISTRAR_H__
*/
