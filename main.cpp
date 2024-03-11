#include  <sys/socket.h>
#include <iostream>

int main()
{
    int i = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << i << std::endl;
}