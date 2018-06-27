#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "mu_test.h"
#include "client.h"
#include "server.h"


#define PORT 8080
#define IP "127.0.0.1"


UNIT(Init)

END_UNIT

UNIT(Create_TCP)
	TCPclient * tcp = NULL;

	tcp = TCPclient_create(8080, "127.0.0.1");

	ASSERT_THAT(tcp);

	TCPclient_destroy(&tcp);

	ASSERT_THAT(tcp == NULL);

END_UNIT

UNIT(runC)
	TCPclient * tcp = NULL;
    char msg[LINE_MAX];
    char buffer[LINE_MAX];

    int n;

	tcp = TCPclient_create(8080, "127.0.0.1");

	while (1)
	{
		printf("Insert message to send.\n");
        scanf("%s", msg);
        strcat(msg, "\n");

        // Send to UDP Server
		n = TCPclient_sendTo(tcp, msg, strlen(msg));
        printf("Message sent - %d bytes\n", n);
            
       	n = TCPclient_receiveFrom(tcp, buffer, LINE_MAX);
        printf("Server : %s\n", buffer); 
	}

	TCPclient_destroy(&tcp);

END_UNIT
	
UNIT(myServerTest)
	TCPclient * tcp = NULL;
    char msg[LINE_MAX] = "Hello From Client";
    int n;

	tcp = TCPclient_create(8080, "127.0.0.1");

	n = TCPclient_sendTo(tcp, msg, strlen(msg));
        printf("Message sent - %d bytes\n", n);
            


	TCPclient_destroy(&tcp);

END_UNIT

TEST_SUITE(TCP)
	IGNORE_TEST(Create_TCP)
	IGNORE_TEST(runC)
	TEST(myServerTest)
END_SUITE
