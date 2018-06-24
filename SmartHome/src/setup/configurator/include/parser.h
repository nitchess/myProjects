/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 31. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Config Parser 
*/ 

#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <string>

class Parser
{
private:
	// Non-Copyable
	Parser(const Parser&);
    Parser& operator = (const Parser&);

public:
	Parser(){}
	~Parser(){}
	
	// parse line
	void ParseLine(std::string& _line);  
};

#endif /*__PARSER_H__*/
