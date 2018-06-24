/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 17. 06. 18
* @dateLastModified : 18. 06. 18
* @brief            : My String Class Header
*/ 
#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <algorithm>
// Buffer Class
#include "buffer.h"
// String Exceptions Class
#include "stringException.h"
#include <cstring>

// Based on "SOLID" concepts
namespace advcpp
{

template<typename T>
class MyString
{
public:
    MyString(const T*  _str);
    // MyString(const MyString & _ms);
    // MyString & operator=(const MyString & _ms);
    // ~MyString() = default;

    MyString & operator+=(const MyString & _ms);
    // MyString & operator+=(const T* _str);

    const T &   operator[] (size_t _index) const;
    T &        operator[] (size_t _index);

    size_t length() const;
    T * cStr();
    const T* cStr() const;
    void myStrCpy(const T * _str, size_t _count);

private:
    size_t  m_count;
    implem::Buffer<T>   m_buffer;

    static size_t myStrLen(const T*  str);

}; // class MyString

/**
* Relational Functions & Operators
**/
template<class T>
MyString<T>& toUpperCase(MyString<T> & _ms);
template<class T>
MyString<T>& toLowerCase(MyString<T> & _ms);
template<typename T>
bool operator<(const MyString<T> & _lhs, const MyString<T> & _rhs);

/**
* Implementations
**/
template<typename T>
inline MyString<T>::MyString(const T * _str)
    :   m_count(myStrLen(_str) + 1)
    ,   m_buffer(m_count)
{
    myStrCpy(_str, m_count);

    return;
}

template<typename T>
inline size_t MyString<T>::length() const
{
    return m_count;
}

template<typename T>
inline T * MyString<T>::cStr()
{
    return m_buffer.begin();
}

template<typename T>
inline const T * MyString<T>::cStr() const
{
    return m_buffer.begin();
}

template<typename T>
T & MyString<T>::operator[] (size_t _index)
{
    if (_index > myStrLen(m_buffer.begin()))
    {
        return (m_buffer.begin()[0]);
    }

    return *(m_buffer.begin() + _index); 
}

template<typename T>
const T &  MyString<T>::operator[] (size_t _index) const
{
    return (*this)[_index];
}

template<typename T>
MyString<T>& MyString<T>::operator+=(const MyString<T> & _other)
{
    size_t tc = _other.m_count + m_count - 1;

    m_buffer.reserve(tc);

    std::copy(_other.m_buffer.begin(), _other.m_buffer.end(), m_buffer.begin() + m_count - 1);
    m_count = tc;

    return *this;
}

/**
* Auxilary
**/
template< >
size_t MyString<char>::myStrLen(const char* _str)
{
    if(_str)
    {
        return strlen(_str); 
    }

    return 0;
}

template< >
size_t MyString<wchar_t>::myStrLen(const wchar_t* _str)
{
    if(_str)
    {
        return std::wcslen(_str); 
    }

    return 0;
}

template<typename T>
void MyString<T>::myStrCpy(const T *  _str, size_t _count)
{
    if(_str)
    {
        std::copy(_str, _str + _count, m_buffer.begin());
    }
    else
    {
        m_buffer.begin()[0] = '\0';
    }

    return;
}

} // namespace advcpp


/**
* Non Class-Member-Functions
**/
namespace advcpp
{

template< >
MyString<char>& toUpperCase(MyString<char> & _ms)
{
    std::transform(_ms.cStr(), _ms.cStr() + _ms.length(), _ms.cStr(), toupper);
    
    return _ms;
}

template< >
MyString<wchar_t>& toUpperCase(MyString<wchar_t> & _ms)
{
    std::transform(_ms.cStr(), _ms.cStr() + _ms.length(), _ms.cStr(), towupper);
    
    return _ms;
}

template< >
MyString<char>& toLowerCase(MyString<char> & _ms)
{
    std::transform(_ms.cStr(), _ms.cStr() + _ms.length(), _ms.cStr(), tolower);
    
    return _ms;
}

template< >
MyString<wchar_t>& toLowerCase(MyString<wchar_t> & _ms)
{
    std::transform(_ms.cStr(), _ms.cStr() + _ms.length(), _ms.cStr(), towlower);
    
    return _ms;
}

// Why dont implicitly convert char * ? because of template class?
template<typename T>
MyString<T> operator+(const MyString<T> & _msA, const MyString<T> & _msB)
{
    MyString<T> t1(_msA);
    MyString<T> t2(_msB);

    t1 += t2;
        
    return t1;
}

template<typename T>
MyString<T> operator+(const char* _msA, const MyString<T> & _msB)
{
    MyString<T> t1(_msA);
    MyString<T> t2(_msB);

    t1 += t2;
        
    return t1;
}

template<typename T>
MyString<T> operator+(const MyString<T> & _msA, const char* _msB)
{
    MyString<T> t1(_msA);
    MyString<T> t2(_msB);

    t1 += t2;
        
    return t1;
}

template<class T>
bool operator<(const MyString<T> & _lhs, const MyString<T> & _rhs)
{
    return std::lexicographical_compare(_lhs.cStr(), _lhs.cStr() + _lhs.length(), _rhs.cStr(), _rhs.cStr() + _rhs.length());        
}

template< >
bool operator<(const MyString<wchar_t> & _lhs, const MyString<wchar_t> & _rhs)
{
    return (wcscmp(_lhs.cStr(), _rhs.cStr()));
    
}

template<typename T>
bool operator==(const MyString<T> & _lhs, const MyString<T> & _rhs)
{
    return (!(_lhs < _rhs) && !(_rhs < _lhs));    
} 

template<typename T>
bool operator!=(const MyString<T> & _lhs, const MyString<T> & _rhs)
{
    return !(!(_lhs < _rhs) && !(_rhs < _lhs));    
} 

} // namespace advcpp

#endif /*__MY_STRING_H__*/
