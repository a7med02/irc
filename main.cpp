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
      //exit(1);
    }
    return n;
}


int main()
{
    int sockfd = perr(socket(AF_INET, SOCK_STREAM, 0), "socket");
    int optval = 1;
    perr(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)), "setsockopt");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    perr(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)), "bind");
    perr(listen(sockfd, 10), "listen");
    int newsockfd = perr(accept(sockfd, NULL, NULL), "accept");
    int flags = perr(fcntl(newsockfd, F_GETFL, 0), "fcntl");
    perr(fcntl(newsockfd, F_SETFL, flags | O_NONBLOCK), "fcntl");
    struct pollfd fds[2];
    fds[0].fd = newsockfd;
    fds[0].events = POLLIN;
    fds[1].fd = 0;
    fds[1].events = POLLIN;
    while (true)
    {
        perr(poll(fds, 2, -1), "poll");
        if (fds[0].revents & POLLIN)
        {
            char buf[1024];
            int n = perr(recv(newsockfd, buf, sizeof(buf), 0), "recv");
            if (n == 0)
            {
                break;
            }
            perr(send(newsockfd, buf, n, 0), "send");
        }
        if (fds[1].revents & POLLIN)
        {
            char buf[1024];
            int n = perr(read(0, buf, sizeof(buf)), "read");
            perr(send(newsockfd, buf, n, 0), "send");
        }
    }
}