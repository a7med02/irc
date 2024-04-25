#pragma once 

#include "Client.hpp"

class Server
{
    private:
        int port;
        std::string  password;
        int server_fd;
        Client client[10];
    public:
        Server(){server_fd = -1;};
        void severInit(char **av);
        void serSocket();
        void Accept();
        int Recieve(int fd);
};