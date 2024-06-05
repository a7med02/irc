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
    while (true)
    {
        int ret = poll(bot.fds.data(), bot.fds.size(), -1);
        if (ret == -1){
            std::cerr << "poll failed" << std::endl;
            return 1;
        }
        if (bot.fds[0].revents & POLLIN){
            clinetName = bot.receiveMessageFromServer(bot.fds[0].fd);
            if (!clinetName.empty()){
                response = bot.sendAndRecivFromApi();
                if (bot.wrongFormat)
                    response = "wrong format try to ask like :give me an advice";
                bot.sendMessageToServer(bot.fds[0].fd, response, clinetName);
                clinetName = "";
            }
        }    
    }
    return 0;
}
