#include "Client.hpp"

Client::Client() {
    Fd = -1;
}

void Client::setFd(int newFd){
    Fd = newFd;
}

int Client::getFd(){
    return Fd;
}

void Client::setIp(std::string newIp){
    Ip = newIp;
}

std::string Client::getIp(){
    return Ip;
}


