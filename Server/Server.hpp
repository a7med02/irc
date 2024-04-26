#pragma once

#include <stdio.h>
 #include <stdlib.h>
#include "Client.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server {
    private:
        int port;
        int serverFd;
        std::vector<Client> clients;
        std::vector<pollfd> pollFds;
    public:
        Server();
        ~Server();
        void serverInit();
        void servSocket();
        void AcceptNewClient();
        void receiveData(int fd);
        void clearClient(int fd);
        void closefds();
};