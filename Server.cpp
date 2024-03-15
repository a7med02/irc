#include "Server.hpp"

void Server::severInit()
{
    port = 4444;
    serSocket();
    std::cout << "Server is running on port " << port << std::endl;
    // Accept();
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


