/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 29. 05. 18
* @brief            : HUB's Distributer Class 
*/ 
#ifndef __DISTRIBUTER_H__
#define __DISTRIBUTER_H__

class iPublisher;
class Registrar;
class iRegistrar;

class Distributer
{
private:
    iPublisher *    m_publisher;
    Registrar  *        m_reg;

    // Non-Copyable
    Distributer(const Distributer & _dist);
    Distributer & operator =(const Distributer & _dist);

public:
    Distributer(iPublisher * _pub, iRegistrar * _reg);

    ~Distributer();
    
    void Run();
};

extern "C"
void * DistributerRun(void * _arg);

#endif /*__DISTRIBUTER_H__*/
