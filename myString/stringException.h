/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 17. 06. 18
* @dateLastModified : 18. 06. 18
* @brief            : My String Class Header
*/ 
#ifndef __S_EXCEP_H__
#define __S_EXCEP_H__

#include <exception>

namespace advcpp
{

class StrException : public std::exception
{
private:
	const char* file;
    int 		line;
    const char* func;
    const char* info;

public:
	StrException(const char* file_, int line_, const char* func_, const char* info_ = "");

    ~StrException() throw();
    
    inline const char* get_file() const { return file; }
    inline int         get_line() const { return line; }
    inline const char* get_func() const { return func; }
    inline const char* get_info() const { return info; }
   
};
    
    advcpp::StrException::StrException(const char* file_, int line_, const char* func_, const char* info_) :
        file (file_),
        line (line_),
        func (func_),
        info (info_)
    {
    }

    advcpp::StrException::~StrException() throw(){}
}

/*
try 
{



}
catch (advcpp::StrException & ex)
{
    std::cout << ex.what() << ex.get_info() << std::endl;
    std::cout << "File: " << ex.get_file() << std::endl;
    std::cout << "Function: " << ex.get_func() << std::endl;
    std::cout << "Line: " << ex.get_line() << std::endl;


} 
catch (std::exception& ex) 
{
    std::cout << "std::exception caught" << std::endl;
    std::cout << ex.what() << std::endl;
}
*/

#endif /*__S_EXCEP_H__*/
