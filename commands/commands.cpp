#include "commands.h"
#include <iostream>
#include "../message_builder.h"
#include "../Channel.h"
#include "../User.h"
#include "../UserManager.h"
#include "../ServerCore.h"

void cap_handler(User &user, Message const &message, ServerCore &core)
{
    return ;
}
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

int check_nick(const std::string str)
{
    if ((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z'))
        return(0);
    for(int i = 0; str[i] ; i++)
    {
        if (((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z')) && (str[i] < 0 || str[i] > 9))
        {
            if (str[i] != '-' && str[i] != '[' && str[i] != ']' && str[i] != '\\' && str[i] != '`' && str[i] != '^' && str[i] != '{' && str[i] != '}')
            {
                return(0);
            }
        }

    }
    return(1);
}

void nick_handler(User &user, Message const &message, ServerCore &core)
{
    //std::cout << "chaneg name for :" << message.get_params()[0] << std::endl;
    std::string msg = message.get_params()[0].substr(0, 9);
    UserManager *_user_man = &core.get_userManager();
    {
        user.send_messsage(bld_err_nonicknamegiven(), false);
        return;
    }
    if (_user_man->get_user(msg) == NULL)
    {
        user.send_messsage(bld_err_nicknameinuse(user), false);
        return;
    }
    if (check_nick(msg) <= 0)
    {
        user.send_messsage(bld_err_erroneusnickname(msg), false);
        return;
    }
    if (user.is_state(User::WAITING_FOR_CONN_1) || user.is_state(User::WAITING_FOR_CONN_2))
    {
        std::cout << "username = " << user.get_nickname() << std::endl; 
        user.set_nickname(msg);
        std::cout << "username = " << user.get_nickname() << std::endl; 
        if (user.is_state(User::WAITING_FOR_CONN_1))
            user.set_state(User::WAITING_FOR_CONN_2);
        else if (user.is_state(User::WAITING_FOR_CONN_2))
            user.set_state(User::CONNECTED);
    }
    if (user.is_state(User::CONNECTED))
    {
        user.send_messsage(bld_nick_msg(user, msg), false);
        user.set_nickname(msg);
    }
}
void user_handler(User &user, Message const &message, ServerCore &core)
{
    //std::cout << message.get_params()[0]<< ' ' << message.get_params()[1] << ' ' << message.get_params()[2] << ' ' << message.get_params()[3] << std::endl;
    if (user.is_state(User::CONNECTED))
    {
        user.send_messsage(bld_err_alreadyregistred(), false);
        return;
    }
    user.set_user(message.get_params()[0], message.get_params()[1], message.get_params()[2], message.get_params()[3]);
    if (user.is_state(User::WAITING_FOR_CONN_1))
        user.set_state(User::WAITING_FOR_CONN_2);
    else if (user.is_state(User::WAITING_FOR_CONN_2))
        user.set_state(User::CONNECTED);
    user.send_messsage(bld_rpl_welcome(user) + "\r\n", true);
}
void join_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager *_chanel_manager = &core.get_channelManager();
    int i = 0;
    std::string name;
    if (message.get_params().size() < 1)
    {
        user.send_messsage(bld_err_needmoreparams(message.get_command()));    
        return;
    }
    _chanel_manager->join(user, message.get_params()[0]);
    // while (1)
    // {
    //     if (i != 0)
    //         i++;
    //     if(message.get_params()[0].find(",", i) != std::string::npos)
    //     {
    //         name = message.get_params()[0].substr(i, message.get_params()[0].find(",", i) - i);
    //         i = message.get_params()[0].find(",", i);
    //         _chanel_manager->join(user, name);
    //     }
    //     else
    //     {
    //         name = message.get_params()[0].substr(i, message.get_params()[0].size() - i);
    //         _chanel_manager->join(user, name);
    //         break;
    //     }
    //}
}
void mode_handler(User &user, Message const &message, ServerCore &core) {}
void part_handler(User &user, Message const &message, ServerCore &core) {
    ChannelManager &_chan_man = core.get_channelManager();
    Channel        *chan      = _chan_man.get_channel(message.get_params()[0]);
    //User           *_user     = core.get_userManager().get_user(user.get_nickname());
    std::cout << "Entered the PART_HANDLER" << std::endl;
    if(chan)
        _chan_man.leave(user, *chan);
    //TODO: else send an error for non existing channel

}
void quit_handler(User &user, Message const &message, ServerCore &core) {}
void pong_handler(User &user, Message const &message, ServerCore &core)
{
    //std::cout << "Pong HANDLED" << std::endl;
    user.set_last_pong();
}
void ping_handler(User &user, Message const &message, ServerCore &core)
{
    user.send_messsage("PONG :" + message.get_params()[0] + "\r\n", false);
}

std::string get_reason(Message const &message)
{
    int i = 0;
    for (int i = 0; i < message.get_params().size(); i++)
    {
        if (message.get_params()[i][0] == ':')
        {
            return(message.get_params()[i]);
            
        }
    }
    return(NULL);
}

void kick_handler(User &user, Message const &message, ServerCore &core){
    ChannelManager *chan_man = &core.get_channelManager();

        for (int i = 0; message.get_params()[i][0] == '#'; i++)
        {
            Channel *chan = chan_man->get_channel(message.get_params()[0]);
            if (chan->is_user_OP(user))
            {
                int j = 0;
                while (message.get_params()[j][0] == '#')
                    j++;
                for(j; message.get_params()[j][0] != ':'; j++)
                {
                    UserManager *user_man = &core.get_userManager();
                    User *user_kick = user_man->get_user(message.get_params()[j]);
                    chan->kick(user, *user_kick, get_reason(message));
                }
            }
        }
}
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
        if (channel)
            channel->broadcast(bld_privmsg_msg(user, *channel, message_), &user);
        else
            user.send_messsage(bld_err_nosuchchannel(channel->get_name()));
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