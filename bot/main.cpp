#include "bot.hpp"

int main(int ac, char **av)
{
    if (ac != 3){
        std::cerr << "Usage: ./bot <password>" << std::endl;
        return 1;
    }
    Bot bot(av[2]);
    std::string response = "";
    std::string clinetName = "";
    size_t contentLength = 0;
    while (true)
    {
        int ret = poll(bot.fds.data(), bot.fds.size(), -1);
        if (ret == -1){
            std::cerr << "poll failed" << std::endl;
            return 1;
        }
        if (bot.fds[0].revents & POLLIN){
            std::cout << "0" << std::endl;
            clinetName = bot.receiveMessageFromServer(bot.fds[0].fd);
            if (clinetName != ""){
                bot.sendToApi(bot.fds);
                bot.fds[1].events = POLLIN;
            }
        }
        if (bot.fds[1].revents & POLLIN){
            std::cout << "1" << std::endl;
            while (response.size() <= contentLength ){
                contentLength += bot.receiveFromApi(bot.fds, response);
                if (response != "" && response.size() > contentLength){
                    std::cout << contentLength << std::endl;
                    std::cout << response << std::endl;
                    exit(-1);
                    bot.sendMessageToServer(bot.fds[0].fd, response, clinetName);
                        bot.fds[1].events = POLLOUT;
                    }
            }
        }
        }
        return 0;
    }