#include  <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include "Server.hpp"

int main()
{
  Server server;
  server.severInit();
}