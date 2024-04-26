#include <iostream>
#include "Bot.hpp"

int main()
{
    Bot bt;
    bt.fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (bt.fdSocket == -1)
        exit(1);
    int opt = 1;
    int status = setsockopt(bt.fdSocket, IPPROTO_TCP , SO_REUSEADDR, &opt, sizeof(opt));
    if (status = -1)
        exit;
    bt.serverAddress.sin_family = AF_INET;
    bt.serverAddress.sin_port = htons(4444);
    bt.serverAddress.sin_addr.s_addr = INADDR_ANY;
    status = bind(bt.fdSocket, (struct sockaddr_in*)&bt.serverAddress, sizeof(sockaddr));
    


}