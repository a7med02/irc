#pragma once

#include <iostream>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <string>

class Client
{
    private:
     int Fd;
     std::string Ip;
     public:
        Client();
        int GetFd();
        void SetFd(int fd);
        void SetIp(std::string ip);
};
