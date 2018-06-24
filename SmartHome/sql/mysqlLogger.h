#ifndef __MY_SQL_LOGGER__
#define __MY_SQL_LOGGER__

#include <mysql++/mysql++.h>
#include <iostream>
#include <iomanip>
#include "event.h"
#include "location.h"

using namespace std;

class MySQLLogger
{
private:
    mysqlpp::Connection conn;

    template<typename T>
    std::string toString(T a)
	{
	    std::ostringstream temp;
	    temp << a;
	    return temp.str();
	}

public:
	MySQLLogger();
	~MySQLLogger();
	
	void insert(Event* event);
	void print();

};

#endif /* __MY_SQL_LOGGER__ */
