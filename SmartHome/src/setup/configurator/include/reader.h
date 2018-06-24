/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 31. 05. 18
* @dateLastModified : 31. 05. 18
* @brief            : Config Publisher Class 
*/ 

#ifndef __READER_H__
#define __READER_H__

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

class Reader
{
private:
	std::ifstream	m_fstream;
	std::string		m_filePath;

public:
	// Default CTOR
	Reader();

	// CTOR - Opens File
	Reader(const std::string _path);

	// DTOR - Closes File
	~Reader();

	bool isGood() {return m_fstream.good();}

	// Open new File
	bool Open(const std::string _path);

	// Close File
	bool Close();

	// Return Line From File
	bool ReadLine(std::string & _line);
};


#endif /*__READER_H__*/
