#include "mysqlLogger.h"
#include <iostream>
#include <fstream>

MySQLLogger::MySQLLogger() : conn(false)
{
    if(!conn.connect("SmartHomeDB", "localhost", "root", "student")) 
    {
        cerr << "DB connection failed: " << conn.error() << endl;
    }
}

MySQLLogger::~MySQLLogger()
{
	conn.disconnect();
}

void MySQLLogger::insert(Event* event)
{
	try
	{
	    std::string eventTime = toString(event->getTimestamp());
	    std::string eventType = event->getType();
	    std::string eventLocation = event->getLocation()->name();
	    
	    mysqlpp::Query query = conn.query();

	    query << "INSERT INTO elog " 
	    << "(`eventTime`, `eventType`, `eventLocation`) " 
	    << "VALUES ('"+eventTime+"', '"+eventType+"', '"+eventLocation+"');";
	    query.execute();
	}
	catch(mysqlpp::Exception e){
		cerr << "problem: " << e.what() << endl;
	}
}

void MySQLLogger::print()
{
	try
	{
		mysqlpp::Query query = conn.query(
	        "select * from elog");
	    mysqlpp::StoreQueryResult result = query.store();

	    for(size_t i = 0; i < result.size(); ++i)
	    {
			cout << result[i]["eventTime"] << "\t"
				<< result[i]["eventType"] << "\t"
				<< result[i]["eventLocation"] << '\n';
	    }
	}
	catch(mysqlpp::Exception e){
		cerr << "problem: " << e.what() << endl;
	}
}
