#include "commands.h"
#include <iostream>
#include "../message_builder.h"
#include "../Channel.h"
#include "../User.h"

void cap_handler(User &user, Message const &message, ServerCore &core){}
void pass_handler(User &user, Message const &message, ServerCore &core)
{
    if (core.get_password() != message.get_params()[0])
    {
        user.set_state(User::WAITING_FOR_QUIT);
    }
    else
        user.set_state(User::WAITING_FOR_CONN_1);
}


void nick_handler(User &user, Message const &message, ServerCore &core)
{
    user.set_nickname(message.get_params()[0]);
    if (user.is_state(User::WAITING_FOR_CONN_1))
        user.set_state(User::WAITING_FOR_CONN_2);
}
void user_handler(User &user, Message const &message, ServerCore &core)
{
    user.set_user(message.get_params()[0], message.get_params()[1], message.get_params()[2], message.get_params()[3]);
    user.set_state(User::CONNECTED);
    user.send_messsage(bld_rpl_welcome(user) + "\r\n", true);
}
void join_handler(User &user, Message const &message, ServerCore &core){
    ChannelManager *_chanel_manager = &core.get_channelManager();
    int i = 0;
    std::string name;
    while (1)
    {
        if (i != 0)
            i++;
        if(message.get_params()[0].find(",", i) != std::string::npos)
        {
            name = message.get_params()[0].substr(i, message.get_params()[0].find(",", i) - i);
            i = message.get_params()[0].find(",", i);
            _chanel_manager->join(user, name);
        }
        else
        {
            name = message.get_params()[0].substr(i, message.get_params()[0].size() - i);
            _chanel_manager->join(user, name);
            break;
        }
    }
}
void mode_handler(User &user, Message const &message, ServerCore &core){}
void part_handler(User &user, Message const &message, ServerCore &core){}
void quit_handler(User &user, Message const &message, ServerCore &core){}
void pong_handler(User &user, Message const &message, ServerCore &core){
    std::cout << "Pong HANDLED" << std::endl;
    user.set_last_pong();
}
void ping_handler(User &user, Message const &message, ServerCore &core){
    user.send_messsage("PONG :" + message.get_params()[0] + "\r\n", false);
}
void kick_handler(User &user, Message const &message, ServerCore &core){}
void topic_handler(User &user, Message const &message, ServerCore &core){}
void whois_handler(User &user, Message const &message, ServerCore &core){}
void privmsg_handler(User &user, Message const &message, ServerCore &core){
    ChannelManager *_chanel_man = &core.get_channelManager();
    if (message.get_params()[0][0] == '#' || message.get_params()[0][0] == '&')
    {
            Channel *channel = _chanel_man->get_channel(message.get_params()[0]);
            std::string message_;
            for (int i = 1; i < message.get_params().size(); i++)
            {
                message_ += message.get_params()[i]; 
            }
            channel->broardcast(message_, &user);
    }
}