#include <iostream>
#include <stdio.h>

#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <limits.h>

#include "ServerCore.h"
#include "command_handler.h"

ServerCore::ServerCore(std::string const &password): _password(password){

}

void    ServerCore::loop(int port)
{
    std::vector<pollfd_t> pfds;
    sockaddr_in ipv4 = {0};
    int fd = 0;
    int ret = 0;
    ipv4.sin_family = AF_INET;
    ipv4.sin_port = htons(port);
    ipv4.sin_addr.s_addr = INADDR_ANY;
    ret = fd = socket(AF_INET, SOCK_STREAM, 0);
    ret |= bind(fd, (sockaddr*)&ipv4, sizeof(ipv4));
    ret |= listen(fd, SOMAXCONN);
    if(ret < 0)
    {
        perror("Ethanol said menfou");
        exit(1);
    }
    {
      pollfd    tmpfd = {0};
      tmpfd.fd = fd;
      tmpfd.events = POLLIN;
      pfds.push_back(tmpfd);
    }
    while ("fisabil al-etan") {
        poll(pfds.data(), pfds.size(), 10000);

        for (int i = 0; i < pfds.size(); i++)
        {
            if ((pfds[i].revents & POLLIN) == 0)
            {
                continue;
            }
            if (pfds[i].fd == fd)
            {
                pollfd tmpfd = {0};
                socklen_t a = 0;
                tmpfd.fd = accept(pfds[i].fd, (sockaddr*)0x01, &a);
                tmpfd.events = POLLIN;
                pfds.push_back(tmpfd);
                this->_user_manager.create_user(tmpfd.fd);
            }
            else
            {
                try
                {
                    User *client = this->_user_manager.get_user(pfds[i].fd);
                    client->recvu();
                    // std::cout << "Ramcho 1" << "\n";
                    while (client->is_message_buffered())
                    {
                        Message msg;
                        client->get_message(msg);
                        // std::cout << "Ramcho 2" << "\n";
                        handle_command(*client, msg, *this);
                    }
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
            }
            
        }
        
    }
    

}