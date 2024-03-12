#include  <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>


int main()
{
    int sockfd ;
    int optval = 1; // is used to set the option value [1 : enable, 0 : disable]
    int optlen; // is used to set the option length
    int addrlen;
    int client_sockfd;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    char buffer[100];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "Failed to create socket" << std::endl;
        return 1;
    }
    int status = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (status == -1)
    {
        std::cout << "Failed to set socket options" << std::endl;
        return 1;
    }
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3500); 
    server_address.sin_zero[7] = '\0';
    status = bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (status == -1)
    {
        std::cout << "Failed to bind socket" << std::endl;
        return 1;
    }
    status = listen(sockfd, 5);
    if (status == -1)
    {
        std::cout << "Failed to listen" << std::endl;
        return 1;
    }
    addrlen = sizeof(client_address);
    client_sockfd = accept(sockfd, (struct sockaddr *)&client_address, (socklen_t *)&addrlen);
    if (client_sockfd == -1)
    {
        std::cout << "Failed to accept" << std::endl;
        return 1;
    }
    std::cout << "Hang \n";
    status = recv(client_sockfd, buffer, 100, 0);
    if (status == -1)
    {
        std::cout << "Failed to receive" << std::endl;
        return 1;
    }
    std::cout << "Received message: " << buffer << std::endl;
    status = send(client_sockfd, "Hello from server\n", 19, 0);
    if (status == -1)
    {
        std::cout << "Failed to send" << std::endl;
        return 1;
    }
    close(client_sockfd);
    close(sockfd);
    return 0;
}