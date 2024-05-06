#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include <sys/poll.h>
#include <vector>
int main()
{
    std::vector<struct pollfd> fds;
    fds.resize(2);
    // std::string buffer = "";
    char buffer[500];
    char address[1024];
    struct addrinfo hints;//  is a pointer to a struct addrinfo that contains input values that are used by getaddrinfo() to specify the type of socket that the caller supports (either a datagram socket or a stream socket), the type of service for the given socket, and the protocol to be used with the socket.
    struct addrinfo*res;// is a pointer to a linked list of one or more addrinfo structures that contain response information about the host.
    struct addrinfo *p;// is a pointer to an addrinfo structure that contains response information about the host.
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int  status =  getaddrinfo("api.weatherapi.com", "http", &hints, &res);
    if (status != 0) {
        std::cerr << "Error: getaddrinfo failed" << std::endl;
        return 1;
    }
    inet_ntop(res->ai_family, &((struct sockaddr_in *)res->ai_addr)->sin_addr, address, sizeof(address));
    fds[0].fd = socket(AF_INET, SOCK_STREAM, 0);
    fds[0].events = POLLOUT;
    if (fds[0].fd == -1) {
        std::cerr << "Error: socket creation failed" << std::endl;
        return 1;
    }
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    server_address.sin_addr.s_addr = inet_addr(address);
    if (connect(fds[0].fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: connection failed" << std::endl;
        return 1;
    }
    std::string request = "GET /v1/current.json?key=0138056553a1462c9f191356240105&q=London&aqi=no HTTP/1.1\r\nHost: api.weatherapi.com\r\n\r\n\r\n";
        send(fds[0].fd, request.c_str(), 1024, 0);
        if (poll(fds.data(), 1, -1) == -1) {
            std::cerr << "Error: poll failed" << std::endl;
            return 1;
        }
            std::string response = ""; 
        if (fds[0].revents & POLLOUT) {
            int bytesReceived = 0;
            while ((bytesReceived = recv(fds[0].fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
                    buffer[bytesReceived] = '\0';
                    response += buffer;
                }
            }
            std::cout << "response:  ----------before\n\n\n\n\n\n" << response << std::endl;
            response = response.substr(response.find("\r\n\r\n") + 4);
            std::cout << "response:  ----------after\n\n\n\n\n\n" << response << std::endl;

        // std::cout << response << std::endl;
    return 0;
    }
