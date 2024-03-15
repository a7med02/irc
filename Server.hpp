#pragma once 

#include "Client.hpp"

class Server
{
    private:
    int port;
    int server_fd;
    Client client[10];
    struct pollfd fds[10];
    public:
    Server(){server_fd = -1;};
    void severInit();
    void serSocket();
    void Accept();
    void Recieve(int fd);
};