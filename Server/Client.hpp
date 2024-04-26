#pragma once

#include <iostream>
#include <stdio.h>
 #include <stdlib.h>
#include <string>
#include <vector>
#include <sys/socket.h>//socket
#include <sys/types.h>//socket
#include <netinet/in.h>//sockaddr_in
#include <unistd.h>
#include <poll.h>

class Client {
    private:
        int Fd;
        std::string Ip;
    public:
        Client();
        int getFd();
        void setFd(int fd);
        void setIp(std::string ip);
        std::string getIp();

};

