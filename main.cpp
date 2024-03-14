#include  <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>

int perr(int n, std::string err)
{
    if (n == -1){
      perror(err.c_str());
      exit(1);
    }
    return n;
}


int main()
{
    int sockfd ;
    int optval = 1; // is used to set the option value [1 : enable, 0 : disable]
    int optlen; // is used to set the option length
    int addrlen;
    int client_sockfd;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    struct pollfd fds;
    fds.events = POLLIN;

    char buffer[100];
    sockfd = perr(socket(AF_INET, SOCK_STREAM, 0), "Failed to create socket");
    perr(fcntl(sockfd, F_SETFL, O_NONBLOCK), "Failed to set non-blocking");
    fds.fd = sockfd;
    int status = perr(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)), "Failed to set socket option");
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = INADDR_ANY; // it represents any address of the machine
    server_address.sin_port = htons(5000); 
    server_address.sin_zero[7] = '\0';
    status = perr(bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)), "Failed to bind socket");
    status = perr(listen(sockfd, 5), "Failed to listen");
    addrlen = sizeof(client_address);
    while (1)
    {
        client_sockfd = perr(accept(sockfd, (struct sockaddr *)&client_address, (socklen_t *)&addrlen), "Failed to accept");
        if (client_sockfd == -1)
        {
          if (errno == EWOULDBLOCK)
          {
            std::cout << "No client is connected" << std::endl;
            sleep(1);
          } else{
            perror("error when accepting connection");
            exit(1);
          }
        } else
        {
            perr(recv(client_sockfd, buffer, 100, 0), "Failed to receive");
            std::cout << "Received message: " << buffer << std::endl;
          std::string msg = "hello from server\n";
          std::cout << "Sending message: " << msg << std::endl;
          perr(send(client_sockfd, msg.c_str(), sizeof(msg), 0), "Failed to send");
          close(client_sockfd);
        }
  }
    close(sockfd);
    return 0;
}