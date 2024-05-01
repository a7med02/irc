#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

/*
connect() function is used to establish a connection to the server.
The connect() function takes three arguments:
-- The file descriptor of the socket that was created using the socket() function.
-- The address of the server to which the connection is to be established.
-- The size of the address of the server.
*/


/*
* recv() function is used to receive data from the server. 
* The recv() function takes four arguments:
* -- The file descriptor of the socket.
* -- The buffer in which the data is to be stored.
* -- The size of the buffer.
* send() function is used to send data to the server.
*/

// void handleCommand(char *buffer) {
//     struct addrinfo *res;
//     if (find(buffer, "adivice") != std::string::npos) {
//         //send to a api to get advice
//         getaddrinfo("https://api.adviceslip.com/advice", NULL, NULL, &res);
//         send(socket_fd, res->ai_addr, 1024, 0);
//         recv(socket_fd, buffer, 1024, 0);0
//         std::cout << buffer << std::endl;
// }


// int main() {
//     int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (socket_fd == -1) {
//         std::cerr << "Error: socket creation failed" << std::endl;
//         return 1;
//     }
//     struct sockaddr_in server_address;
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(4444);
//     server_address.sin_addr.s_addr = INADDR_ANY;
//     char buffer[1024];
//     memset(buffer, 0, 1024);
//     while (true) {
//     if (connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
//         std::cerr << "Error: connection failed" << std::endl;
//         return 1;
//     }
    
//     send(socket_fd, "Pass <password>", 1024, 0);
//     send(socket_fd, "Nick <message>", 1024, 0);
//     send(socket_fd, "User <message>", 1024, 0);
//     recv(socket_fd, buffer, 1024, 0);0
//     handleCommand(buffer);
//     }

//   }
// }


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
    api_address.sin_addr.s_addr = res->ai_addr.;
    char buffer[1024];
    memset(buffer, 0, 1024);


    while (true)
    {
        // if (connect(bot_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        // {
        //     std::cerr << "Error: connection failed" << std::endl;
        //     return 1;
        // }
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