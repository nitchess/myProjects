/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 31. 05. 18
* @dateLastModified : 05. 06. 18
* @brief            : Config Parser Class 
*/ 

#include "parser.h"

using namespace std;

void Parser::ParseLine(std::string& _line)
{
    std::string delimiter = "=";
    std::string tokens = "^=[]{}+\t ";
    size_t pos = 0;

    // find first "="
    while ((pos = _line.find(delimiter)) != std::string::npos)
    {
    	// Erase string from 0 to delimiter(include)
        _line.erase(0, pos + delimiter.length());
    }

    // erase any other punctuations
    size_t found = _line.find_first_of(tokens);
    while (found != std::string::npos)
    {
        _line.erase(found, 1);
        found = _line.find_first_of(tokens);
    }

    return;
}
