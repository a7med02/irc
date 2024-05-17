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

void receiving_messageFromServer(int fd){
    char buffer[1024];
    int n = recv(fd, buffer, 1024, 0);
    if (n < 0){
        std::cout << "Error receiving message" << std::endl;
        return;
    }
    buffer[n] = '\0';
    std::cout << buffer << std::endl;
}

void receiving_messageFromAPI(int fd){
    char buffer[1024];
    int n = recv(fd, buffer, 1024, 0);
    if (n < 0){
        std::cout << "Error receiving message" << std::endl;
        return;
    }
    buffer[n] = '\0';
    std::cout << buffer << std::endl;
}


int main(int ac, char **av)
{
    char buffer[1024];
    char adderss[1024];
    struct addrinfo hints;
    struct addrinfo *res;

    std::string argv = av[2];
    std::vector<struct pollfd> fds;
    struct sockaddr_in serv_addr;
    struct sockaddr_in api_addr;
    int port = 8080;
    fds.resize(2);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo("api.weatherapi.com", "http", &hints, &res);
    if (status != 0)
    {
        std::cerr << "Error : getaddinfo filed" << std::endl;
        return 1;
    }
    inet_ntop(res->ai_family, &((struct sockaddr_in *)res->ai_addr)->sin_addr, adderss, sizeof(adderss));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    fds[0].fd = socket(AF_INET, SOCK_STREAM, 0);
    fds[0].events = POLLIN | POLLOUT;
    fds[1].fd = socket(AF_INET, SOCK_STREAM, 0);
    fds[1].events = POLLIN | POLLOUT;
    if (fds[0].fd < 0 || fds[1].fd < 0){
        std::cout << "Error creating socket" << std::endl;
        return 1;
    }
    if (connect(fds[0].fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Error connecting to server" << std::endl; 
        return 1;
    }
    // else if (connect(fds[1].fd, (struct sockaddr *)&api_addr, sizeof(api_addr)) < 0){
    //     std::cout << "Error connecting to api" << std::endl; 
    //     return 1;
    // }
    std::string passCmd = "PASS " + argv + "\r\n";
    std::string nickCmd = "NICK bot\r\n";
    std::string userCmd = "USER bot 0 * realbot\r\n";
    // if (send(fds[0].fd, &passCmd , 5 + passCmd.size(), 0) < 0){
    //     std::cout << "Error sending message" << std::endl;
    //     return 1;
    // }
    // while (1){
        if (poll(fds.data(), fds.size(), -1) < 0){
            std::cout << "Error polling" << std::endl;
            return 1;
        }
        if (fds[0].revents & POLLOUT){
            if (send(fds[0].fd, passCmd.c_str() ,passCmd.size(), 0) < 0){
                std::cout << "Error sending message" << std::endl;
                return 1;
            } 
            sleep(1);
            if (send(fds[0].fd, nickCmd.c_str() , nickCmd.size(), 0) < 0){
                std::cout << "Error sending message" << std::endl;
                return 1;
            }
            sleep(1);
            if (send(fds[0].fd, userCmd.c_str(), userCmd.size(), 0) < 0){
                std::cout << "Error sending message" << std::endl;
                return 1;
            }
            sleep(1);
            fds[0].revents = POLLIN;
        // }
        // }
        // if (fds[1].revents && POLLOUT)
        //     if (send(fds[1].fd, &requsetToServer , 5 + requsetToServer.size(), 0) < 0){
        //         std::cout << "Error sending message" << std::endl;
        //         return 1;
        //     }
        while (1)
        {
        if (fds[0].revents & POLLIN)
            receiving_messageFromServer(fds[0].fd);
        if (fds[1].revents & POLLIN)
            receiving_messageFromAPI(fds[1].fd);
            }
    }
}




// size_t nbt = recv(fds[0].fd, buffer, 1024, 0);
//             buffer[nbt] = '\0';
//             std::string temp = buffer;
//             std::string type = typeOfResponse(temp);
//             if (type == "Content-Length") {
//                 // std::cout << "Content-Length" << std::endl;
//                 response += contentLength(temp, fds, buffer);
//                 break;
//             }
//             else if (type == "chunked") {
//                 // std::cout << "chunked" << std::endl;
//                 response += chunked(temp, fds, buffer);
//                 break;
//             }
//     response = parse(response);