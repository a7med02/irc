#include "Client.hpp"


Client::Client()
{
    Fd = -1;
    Ip = "";
}

int Client::GetFd()
{
    return Fd;
}

void Client::SetFd(int fd)
{
    Fd = fd;
}

void Client::SetIp(std::string ip)
{
    Ip = ip;
}
