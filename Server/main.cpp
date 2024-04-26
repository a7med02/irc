#include "Server.hpp"
#include <iostream>
#include "Client.hpp"

int main(int ac, char **av){
    (void)ac;
    (void)av;
    Server server;
    server.serverInit();
    server.closefds();
    return 0;
}