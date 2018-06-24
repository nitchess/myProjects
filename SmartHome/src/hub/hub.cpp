/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 28. 05. 18
* @dateLastModified : 29. 05. 18
* @brief            : HUB Class Implementation
*/

#include <pthread.h>
#include <unistd.h>

#include "hub.h"
#include "publisher.h"
#include "registrar.h"
#include "distributer.h"

Hub::Hub()
{
	// shared ptr
    m_pub = new Publisher;
    m_reg = new Registrar;
    m_dis = new Distributer(m_pub, m_reg);
}

Hub::~Hub()
{
    delete m_pub;
    delete m_reg;
    delete m_dis;
}

void Hub::Run()
{
    pthread_create(&m_disThread, 0, DistributerRun, m_dis);

    return;
}

