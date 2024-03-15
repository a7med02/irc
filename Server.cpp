#include "Server.hpp"
#include <arpa/inet.h>
#include "unistd.h"

void Server::severInit()
{
    port = 4444;
    serSocket();
    std::cout << "Server is running on port " << port << std::endl;
    while(1)
    {
        if (poll(&fds[0], 10, -1) == -1)
        {
            perror("poll");
            exit(1);
        }
        for (int i = 0; i < 10; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == server_fd)
                {
                    Accept();
                }
                else
                {
                    Recieve(fds[i].fd);
                }
            }
        }
    }
    close(server_fd);
    // close(client[0].GetFd());
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
    if (fcntl(server_fd, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("fcntl");
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
    fds[0] = newPoll;
}

void Server::Accept()
{
    Client newClient;
    struct pollfd newPoll;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int new_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
  

    if (new_fd == -1)
    {
        perror("accept");
        exit(1);
    }
    if (fcntl(new_fd, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("fcntl");
        exit(1);
    }
    newPoll.fd = new_fd;
    newPoll.events = POLLIN;
    newPoll.revents = 0;
    newClient.SetFd(new_fd);
    newClient.SetIp(inet_ntoa(client_addr.sin_addr));
    for (int i = 0; i < 10; i++)
    {
        if (client[i].GetFd() == -1)
        {
            client[i] = newClient;
            fds[i] = newPoll;
            break;
        }
    }
    std::cout << "New connection " << std::endl;

}

#include <cstring>

void Server::Recieve(int fd)
{
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));

    ssize_t bytes = recv(fd, buffer, sizeof(buffer), -1, 0);
    if (bytes <= 0){
        std::cout << "Connection closed" << std::endl;
        for (int i = 0; i < 10; i++)
        {
            if (client[i].GetFd() == fd)
            {
                client[i].SetFd(-1);
                break;
            }
        }
    }
    else
    {
        buffer[bytes] = '\0';
        std::cout << "Recieved: " << buffer << std::endl;
    }
}