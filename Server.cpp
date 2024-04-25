#include "Server.hpp"
#include <arpa/inet.h>
#include "unistd.h"
#include <vector>
typedef struct pollfd poly;
std::vector<poly> fds;
void Server::severInit(char **av)
{
    port = std::stoi(av[1]);
    password = av[2];
    serSocket();
    std::cout << "Server is running on port " << port << std::endl;
    while(1)
    {
        int pol = poll(fds.data(), 10, 2000);
        if (pol == -1)
        {
            perror("poll");
            exit(1);
        }
        if (pol == 0)
            continue;
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (i == 0 && fds[0].revents & POLLIN)
                    Accept();

            else if (fds[i].revents & POLLIN)
                if (Recieve(fds[i].fd) == 1)
                    exit(1);
                
        }
    }
    close(server_fd);
}

void Server::serSocket()
{
    struct sockaddr_in addr;
    struct pollfd newPoll;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket");
        exit(1);
    }
    int optval = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if (listen(server_fd, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    newPoll.fd = server_fd;
    newPoll.events = POLLIN;
    newPoll.revents = 0;
    fds.push_back(newPoll);
}

void Server::Accept()
{
    Client newClient;
    struct pollfd newPoll;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int new_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
  
    newPoll.fd = new_fd;
    newPoll.events = POLLIN;
    newPoll.revents = 0;
    fds.push_back(newPoll);

    if (new_fd == -1)
    {
        perror("accept");
        exit(1);
    }
    std::cout << "New connection " << std::endl;

}

#include <cstring>

int Server::Recieve(int fd)
{
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));

    ssize_t bytes = recv(fd, buffer, sizeof(buffer), 0);
    if (bytes <= 0){
        std::cout << "Connection closed" << std::endl;
        return 1;
        for (int i = 0; i < 10; i++)
        {
            if (client[i].GetFd() == fd)
            {
                client[i].SetFd(-1);
                return 0;
            }
        }
    }
    else
    {
        buffer[bytes] = '\0';
        std::cout << "Recieved: " << buffer;
    }
    return 0;
}