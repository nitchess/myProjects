#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <memory>

#include "publisher.h"
#include "event.h"

using namespace std;

void* ConsumerThread(void *arguments)
{
    Publisher * pub = static_cast<Publisher *>(arguments);

    while (true)
    {
        time_t eventTS;

        shared_ptr<Event> data;

        data = pub->PopEvent();

        eventTS = data->GetTimestamp();

        cout << asctime(localtime(&eventTS)) << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    try
    {
        Publisher pub;

        // Create the consumer
        pthread_t consumer;
        pthread_create(&consumer, 0, ConsumerThread, &pub);

        // Start producing
        while(true)
        {
            shared_ptr<Event> test_event(new Event);
            pub.PushEvent(test_event);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "exception caught: " << e.what() << '\n';
    }

    return 0;
}
