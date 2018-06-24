/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 17. 06. 18
* @dateLastModified : 18. 06. 18
* @brief            : String Buffer Class Header
*/
#ifndef __Buffer_H__
#define __Buffer_H__

// For string ops
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <cassert>

namespace advcpp
{

namespace implem
{

template<typename T>
class Buffer
{
public:
    // CTOR from size, will allocate number of T elements
    explicit Buffer(size_t _c);

    Buffer(const Buffer & _b);
    Buffer & operator=(const Buffer & _b);
    ~Buffer();

    // Buffer & operator[](const Buffer & _b);
    void swap(Buffer& other);

    const T* begin() const;
    T*       begin();

    const T* end() const;
    T*       end();

    // Realloc buffer cpacity if needed.
    // Will not shrink the buffer if the original size is bigger than the new size.
    void reserve(size_t _newS);
    
    size_t  size() const;
    size_t  capacity() const;
    
private:
    size_t  m_size;
    size_t  m_capacity;
    T *     m_data;

    static size_t alignToNextPowerOf2(size_t _capacity);

}; // Class Buffer

template<typename T>
inline Buffer<T>::Buffer(size_t _c)
    :   m_size(_c)
    ,   m_capacity(alignToNextPowerOf2(m_size))
    ,   m_data(new T[m_size])   
{
    return;
}

template<typename T>
inline Buffer<T>::~Buffer()
{
    delete[] m_data;

    return;
}

template<typename T>
inline Buffer<T>::Buffer(const Buffer& rhs)
    :   m_size(rhs.m_size)
    ,   m_capacity(alignToNextPowerOf2(m_size))
    ,   m_data(new T[m_size]) 
{
    using std::copy;

    copy(rhs.begin(), rhs.end(), begin());     
    
    return;
}
    
template<typename T>
inline Buffer<T>& Buffer<T>::operator=(Buffer const& rhs)
{
    Buffer t(rhs);

    swap(t);
    
    return *this;
}


template<typename T>
inline void Buffer<T>::swap(Buffer& other)
{
    // no throw
    using std::swap;
    
    swap(m_size, other.m_size);
    swap(m_capacity, other.m_capacity);
    swap(m_data, other.m_data);

    return;
}

template<typename T>
inline void Buffer<T>::reserve(size_t _newS)
{
    if (m_capacity >= _newS)
    {
        // std::cout << "Capacity: " << m_capacity << std::endl;
        return;
    }
    else
    {
        _newS = ((_newS * 3) / 2);
    }

    Buffer t(_newS);

    std::copy(begin(), end(), t.begin());

    swap(t);

    return;
}
    
template<typename T>
inline const T* Buffer<T>::begin() const
{
    return m_data;
}
    
template<typename T>
inline const T* Buffer<T>::end() const
{
    return m_data + m_size;
}

template<typename T>
inline T* Buffer<T>::begin()
{
    return m_data;
}
    
template<typename T>
inline T* Buffer<T>::end()
{
    return m_data + m_size;
}

template<typename T>
inline size_t Buffer<T>::capacity() const
{
    return m_capacity; 
}

template<typename T>
inline size_t Buffer<T>::size() const
{
    return m_size; 
}

template<typename T>
size_t Buffer<T>::alignToNextPowerOf2(size_t _capacity)
{
    size_t counter = 0;

    if (_capacity == 0)
    {
        return 2;
    }

    while (_capacity > 0)
    {
        ++counter;
        _capacity = _capacity >> 1;
    }

    return (1 << counter);
}

}// namespace implem

} // namespace advcpp

#endif /*__Buffer_H__*/
