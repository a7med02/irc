#pragma once 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string.h>
#include <stdlib.h>

class Bot
{
    
    public:
        int fdBotSocket;
        int fdSocket;
        char storageBuffer[256];
        int lenOfAddress;
        struct sockaddr_in serverAddress;
        struct sockaddr_in connectionAddress;
};