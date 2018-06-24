/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 03. 06. 18
* @dateLastModified : 05. 06. 18
* @brief            : Config Publisher Implementation 
*/ 

#include "reader.h"

using namespace std;

Reader::Reader()
{
	m_filePath = '0';
}

Reader::Reader(const std::string _path)
{
	m_filePath = _path;

	m_fstream.open(m_filePath.c_str(), fstream::in);
}

Reader::~Reader()
{
	m_fstream.close();
}

bool Reader::Open(const std::string _path)
{
	m_filePath = _path;

	m_fstream.open(m_filePath.c_str(), fstream::in);

	return (m_fstream.is_open());
}

bool Reader::Close()
{
	m_fstream.close();

	return(!m_fstream.is_open());
}

bool Reader::ReadLine(std::string & _line)
{
	if (m_fstream.good())
	{
		if(getline(m_fstream, _line))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}
