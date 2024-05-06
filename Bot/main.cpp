#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int main()
{
    int bot_socket;
    struct sockaddr_in server_address;
    struct sockaddr_in api_address;
    bot_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (bot_socket == -1)
    {
        std::cerr << "Error: socket creation failed" << std::endl;
        return 1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4444);
    server_address.sin_addr.s_addr = INADDR_ANY;

    struct addrinfo *res;
    api_address.sin_family = AF_INET;
    api_address.sin_port = htons(433);
    getaddrinfo("api.adviceslip.com", NULL, NULL, &res);
    api_address.sin_addr.s_addr = res->ai_addr.sin_addr.s_addr;
    char buffer[1024];
    memset(buffer, 0, 1024);


    while (true)
    {
        if (connect(bot_socket, (struct sockaddr *)&api_address, sizeof(server_address)) == -1)
        {
            std::cerr << "Error: connection failed" << std::endl;
            return 1;
        }
        send(bot_socket, res->ai_addr, 1024, 0);
        recv(bot_socket, buffer, 1024, 0);
        std::cout << buffer << std::endl;
    }

}