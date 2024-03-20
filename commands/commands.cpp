#include "commands.h"
#include <iostream>
#include "../message_builder.h"
#include "../Channel.h"
#include "../User.h"

void cap_handler(User &user, Message const &message, ServerCore &core){}
void pass_handler(User &user, Message const &message, ServerCore &core)
{
    if (user.is_state(User::CONNECTED))
    {
        user.send_messsage(bld_err_alreadyregistred(), false);
    }
    if (core.get_password() != message.get_params()[0])
    {
        user.set_state(User::WAITING_FOR_QUIT);
    }
    else
        user.set_state(User::WAITING_FOR_CONN_1);
}


void nick_handler(User &user, Message const &message, ServerCore &core)
{
    //std::cout << "chaneg name for :" << message.get_params()[0] << std::endl;
    if (message.get_params().size() < 0)
    {
        user.send_messsage(bld_err_nonicknamegiven(), false);
        return;
    }
    if (message.get_params()[0] == user.get_nickname())
    {
        user.send_messsage(bld_err_nicknameinuse(user), false);
        return;
    }
    if (message.get_params()[0].size() > 9 || )
    if (user.is_state(User::WAITING_FOR_CONN_1) || user.is_state(User::WAITING_FOR_CONN_2))
    {
        std::cout << "username = " << user.get_nickname() << std::endl; 
        user.set_nickname(message.get_params()[0]);
        std::cout << "username = " << user.get_nickname() << std::endl; 
        if (user.is_state(User::WAITING_FOR_CONN_1))
            user.set_state(User::WAITING_FOR_CONN_2);
        else if (user.is_state(User::WAITING_FOR_CONN_2))
            user.set_state(User::CONNECTED);
    }
    if (user.is_state(User::CONNECTED))
    {
        UserManager *_user_man = &core.get_userManager();
        user.send_messsage(bld_nick_msg(user, message.get_params()[0]), false);
        user.set_nickname(message.get_params()[0]);
    }
}
void user_handler(User &user, Message const &message, ServerCore &core)
{
    //std::cout << message.get_params()[0]<< ' ' << message.get_params()[1] << ' ' << message.get_params()[2] << ' ' << message.get_params()[3] << std::endl;
    user.set_user(message.get_params()[0], message.get_params()[1], message.get_params()[2], message.get_params()[3]);
    if (user.is_state(User::WAITING_FOR_CONN_1))
        user.set_state(User::WAITING_FOR_CONN_2);
    else if (user.is_state(User::WAITING_FOR_CONN_2))
        user.set_state(User::CONNECTED);
    user.send_messsage(bld_rpl_welcome(user) + "\r\n", true);
}
void join_handler(User &user, Message const &message, ServerCore &core){
    ChannelManager *_chanel_manager = &core.get_channelManager();
    int i = 0;
    std::string name;
    if (message.get_params().size() < 1)
    {
        user.send_messsage(bld_err_needmoreparams(message.get_command()));
        return;
    }
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
    //std::cout << "Pong HANDLED" << std::endl;
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
    std::string message_;
    if (message.get_params().size() < 1)
    {
        user.send_messsage("412 :No text to send");
        return;
    }
    for (int i = 1; i < message.get_params().size(); i++)
    {
        message_ += message.get_params()[i]; 
    }
    if (message.get_params()[0][0] == '#' || message.get_params()[0][0] == '&')
    {
        Channel *channel = _chanel_man->get_channel(message.get_params()[0]);
        channel->broardcast(message_, &user);
    }
    else
    {
        UserManager *user_man = &core.get_userManager();
        User *recipient_user = user_man->get_user(message.get_params()[0]);
        //std::cout << bld_err_nosuchnick(message.get_params()[0]) << std::endl;
        if (recipient_user == NULL)
            user.send_messsage(bld_err_nosuchnick(message.get_params()[0]), false);
        else
            recipient_user->send_messsage(bld_privmsg_msg(user, *recipient_user, message_), false);
    }
}