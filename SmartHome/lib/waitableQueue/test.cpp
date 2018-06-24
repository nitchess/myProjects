#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include "waitableQueue.h"

#define TYPE int

using namespace std;

void* ConsumerThread(void *arguments)
{
    WaitableQueue<TYPE*> * wq = static_cast<WaitableQueue<TYPE*>*>(arguments);

    while (true)
    {
        TYPE* data = NULL;

        data = wq->Pop();

        cout << *data << endl;

        if (data != NULL)
        {
            delete[] data;
        }
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    WaitableQueue<TYPE*> wq;
    TYPE i = 15;

    // Create the consumer
    pthread_t consumer;
    pthread_create(&consumer, NULL, ConsumerThread, &wq);

    // Start producing
    while (true)
    {
        TYPE* test_data = new TYPE;
        *test_data = i++;
        wq.Push(test_data);
    }

    return 0;
}
