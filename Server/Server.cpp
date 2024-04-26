#include "Server.hpp"
#include <cstring>
#include <stdio.h>

Server::Server() {
    serverFd = -1;
}

void Server::AcceptNewClient(){
    // we need to store the client's IP address and port number.
    //[information about the client is stored in the sockaddr_in structure]
    Client newClient;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    struct pollfd newpollfd;

    //accept() function is used to accept the incoming connection from the client.
    // The accept() function returns a new file descriptor that is used to communicate with the client.
    int incomingFd = accept(serverFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if(incomingFd == -1){
        perror("accept");
        return;
    }
    // The new file descriptor is added to the pollfd structure so that we can wait for events on it.
    newpollfd.fd = incomingFd;
    newpollfd.events = POLLIN;
    newpollfd.revents = 0;

    newClient.setFd(incomingFd);
    newClient.setIp(inet_ntoa(clientAddr.sin_addr));
    // The IP address of the client is stored in the clientAddr structure.
    // The IP address is converted to a string using the inet_ntoa() function.
    pollFds.push_back(newpollfd);
    // The new client is added to the clients vector.
    // The new file descriptor is added to the pollFds vector.
    clients.push_back(newClient);
    std::cout << "New connection from " << newClient.getIp() << std::endl;
}


void Server::receiveData(int fd){
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int ret = recv(fd, buffer, sizeof(buffer),0);
    // -1 is used to receive the data with the MSG_WAITALL flag. 
    //MSG_WAITALL flag is used to wait until all the data is received,
 
    //and 0 is used to receive the data with the MSG_PEEK flag. 
    //MSG_PEEK flag is used to peek at the data without removing it from the socket.
    if(ret == -1){
        perror("recv");
        clearClient(fd);
        return;
    }
    if(ret == 0){
        clearClient(fd);
        return;
    }
    std::cout << "Received data: " << buffer << std::endl;
}






void Server::servSocket(){
// the server address structure is initialized 
//with the server's IP address and port number using the bind() function //and the server socket is created using the socket() function.
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port); // host to network short (16-bit) 
    //converts the port number to network byte order using the htons() function.
    servAddr.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY is used to bind the socket to all available interfaces on the machine.

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverFd == -1){
        perror("socket");
        exit(1);
    }
    int opt = 1;
    if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1){
        perror("setsockopt");
        exit(1);
    }
    if(bind(serverFd, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1){
        perror("bind");
        exit(1);
    }
    if(listen(serverFd, 5) == -1){
        perror("listen");
        exit(1);
    }
    pollfd newpollfd;
    newpollfd.fd = serverFd;
    newpollfd.events = POLLIN;
    newpollfd.revents = 0;
    pollFds.push_back(newpollfd);
}

void Server::serverInit(){
    this->port = 4444;
    servSocket();
    std::cout << "Server is running on port " << port << std::endl;
    std::cout << "Waiting for connections..." << std::endl;
    while(1){
        int ret = poll(pollFds.data(), pollFds.size(), -1);//poll() function is used to wait for events on the file descriptors.//- 1 is used to wait indefinitely for an event to occur. 
        if(ret == -1){
            perror("poll");
            exit(1);
        }
        for (size_t i = 0; i < pollFds.size(); i++){
            if (pollFds[i].revents & POLLIN){
                if (pollFds[i].fd == serverFd){
                    AcceptNewClient();
                } else {
                    receiveData(pollFds[i].fd);
                }
}
        }  
    }
}

Server::~Server(){
    closefds();
}

void Server::clearClient(int fd){
    close(fd);
    for (size_t i = 0; i < clients.size(); i++){
        if (clients[i].getFd() == fd){
            std::cout << "Client " << clients[i].getIp() << " disconnected" << std::endl;
            clients.erase(clients.begin() + i);
            pollFds.erase(pollFds.begin() + i);
            break;
        }
    }
}

void Server::closefds(){
    for (size_t i = 0; i < clients.size(); i++){
        close(clients[i].getFd());
    }
    close(serverFd);
}