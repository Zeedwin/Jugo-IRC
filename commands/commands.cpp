#include "commands.h"
#include <iostream>
#include "../message_builder.h"
#include "../Channel.h"
#include "../User.h"
#include "../UserManager.h"
#include "../ServerCore.h"
#include <string> 
std::string get_arg(std::string str)
{
    std::string str2;
    size_t i = str.find(',');
    if (i == std::string::npos)
    {
        return(str);
    }
    str2 = str.substr(0, i);
    return(str2);
}
void cap_handler(User &user, Message const &message, ServerCore &core)
{
    return;
}
void pass_handler(User &user, Message const &message, ServerCore &core)
{
    if (user.is_state(User::CONNECTED))
    {
        user.send_messsage(bld_err_alreadyregistred(), false);
    }
    if (core.get_password() != message.get_params()[0])
    {
        std::cout << "3er pos ?" << std::endl;
        user.set_state(User::WAITING_FOR_QUIT);
    }
    else
    {
        // std::cout << "oookkkkk 1 " << std::endl;
        user.set_state(User::WAITING_FOR_CONN_1);
    }
}

int check_nick(const std::string str)
{
    if ((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z'))
        return (0);
    for (int i = 0; str[i]; i++)
    {
        if (((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z')) && (str[i] < 0 || str[i] > 9))
        {
            if (str[i] != '-' && str[i] != '[' && str[i] != ']' && str[i] != '\\' && str[i] != '`' && str[i] != '^' && str[i] != '{' && str[i] != '}')
            {
                return (0);
            }
        }
    }
    return (1);
}

void nick_handler(User &user, Message const &message, ServerCore &core)
{
    // std::cout << "chaneg name for :" << message.get_params()[0] << std::endl;
    std::string msg = message.get_params()[0].substr(0, 9);
    UserManager *_user_man = &core.get_userManager();
    if (message.get_params().size() < 1)
    {
        user.send_messsage(bld_err_nonicknamegiven(), false);
        return;
    }
    if (_user_man->get_user(msg) != NULL)
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
        // std::cout << "username = " << user.get_nickname() << std::endl;
        user.set_nickname(msg);
        // std::cout << "username = " << user.get_nickname() << std::endl;
        if (user.is_state(User::WAITING_FOR_CONN_1))
            user.set_state(User::WAITING_FOR_CONN_2);
        else if (user.is_state(User::WAITING_FOR_CONN_2))
            user.set_state(User::CONNECTED);
    }
    else if (user.is_state(User::CONNECTED))
    {
        user.send_messsage(bld_nick_msg(user, msg), false);
        user.set_nickname(msg);
    }
}
void user_handler(User &user, Message const &message, ServerCore &core)
{
    // std::cout << message.get_params()[0]<< ' ' << message.get_params()[1] << ' ' << message.get_params()[2] << ' ' << message.get_params()[3] << std::endl;
    if (user.is_state(User::CONNECTED))
    {
        user.send_messsage(bld_err_alreadyregistred(), false);
        return;
    }
    user.set_user(message.get_params()[0], message.get_params()[1], message.get_params()[2], message.get_params()[3]);
    if (user.is_state(User::WAITING_FOR_CONN_1))
        user.set_state(User::WAITING_FOR_CONN_2);
    else if (user.is_state(User::WAITING_FOR_CONN_2))
    {
        // std::cout << "on l'a faaaiiiiittt " << std::endl;
        user.set_state(User::CONNECTED);
    }
    user.send_messsage(bld_rpl_welcome(user) + "\r\n", true);
}
void join_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager &_chanel_manager = core.get_channelManager();
    int pos = 0;
    std::string chans = message.get_params()[0];
    while(chans.size() > 0)
    {
        std::string cha_name = get_arg(chans);
        Channel *chan = _chanel_manager.get_channel(cha_name);
        if(chans.find(',') != std::string::npos)
        {
            chans = chans.substr(chans.find(',') + 1, chans.size() - chans.find(','));
        }
        else
            chans = "";
        _chanel_manager.join(user, cha_name);
    }
    /*if (message.get_params().size() < 1)
    {
        user.send_messsage(bld_err_needmoreparams(message.get_command()));
        return;
    }
    while ((pos = chanlist.find(",")) != (int)std::string::npos) {
        std::string channame = message.get_params()[0].substr(0, pos);
        Channel *chan = _chanel_manager.get_channel(channame);
        std::cout << "Join channame: " << channame << std::endl;
        _chanel_manager.join(user, channame);
        chanlist.erase(0, pos + 1);
    }*/
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
void part_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager &_chan_man = core.get_channelManager();
    std::string message_;
    int pos = 0;
    std::string chanlist = message.get_params()[0];

    while (chanlist.size() > 0) {
        std::string channame = get_arg(chanlist);
        if (chanlist.find(',') != std::string::npos)
        {
            chanlist = chanlist.substr(chanlist.find(',') + 1, chanlist.size() - chanlist.find(','));
        }
        else{
            chanlist = "";
        }
        Channel *chan = _chan_man.get_channel(channame);
        if (chan)
            _chan_man.leave(user, *chan, message_);
        else
            user.send_messsage(bld_err_nosuchchannel(channame));
    }
}
void quit_handler(User &user, Message const &message, ServerCore &core) {}
void pong_handler(User &user, Message const &message, ServerCore &core)
{
    // std::cout << "Pong HANDLED" << std::endl;
    user.set_last_pong();
}
void ping_handler(User &user, Message const &message, ServerCore &core)
{
    user.send_messsage("PONG :" + message.get_params()[0] + "\r\n", false);
}


void kick_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager &chan_man = core.get_channelManager();
    std::cout << "on est la" << std::endl;
    std::string chans = message.get_params()[0];
    while (chans.size() > 0)
    {
        Channel *chan = chan_man.get_channel(get_arg(chans));
        if(chans.find(',') != std::string::npos)
        {
            chans = chans.substr(chans.find(',') + 1, chans.size() - chans.find(','));
        }
        else
            chans = "";
        if (chan == NULL)
        {
            user.send_messsage(bld_err_nosuchchannel(chan->get_name()), false);
        }
        else if (chan->is_user_present(user.get_nickname()) == 0)
        {
            user.send_messsage(bld_err_notonchannel(chan->get_name()), false);
        }
        else if (chan->is_user_OP(user))
        {

            std::string users = message.get_params()[1];
            while (users.size() > 0)
            {
                std::cout << "chan = " << users << std::endl;
                UserManager &user_man = core.get_userManager();
                User *user_kick = user_man.get_user(get_arg(users));
                std::string user_name = get_arg(users);
                if(users.find(',') != std::string::npos)
                    users = users.substr(users.find(',') + 1, users.size() - users.find(','));
                else
                    users = "";
                if (user_kick == NULL)
                {
                    user.send_messsage(bld_err_nosuchnick(user_name), false);
                    continue;
                }
                if (message.get_params().size() == 3)
                    chan->kick(user, *user_kick, message.get_params()[2]);
                else
                    chan->kick(user, *user_kick, "");
                    std::cout << "on va kick lui la " << std::endl;
            }
        }
        else
        {
            user.send_messsage(bld_err_chanoprivsneeded(*chan), false);
        }
    }
}

void topic_handler(User &user, Message const &message, ServerCore &core) {
    ChannelManager *_chanel_man = &core.get_channelManager();
    Channel *channel = _chanel_man->get_channel(message.get_params()[0]);
    std::cout << "TES RAMCHO de loco " << message.get_params()[1] << std::endl;
    if (!channel)
    {
        user.send_messsage(bld_err_nosuchchannel(channel->get_name()));
        return ;
    }
    if (channel->get_name() != message.get_params()[0])
        user.send_messsage(bld_err_nosuchchannel(message.get_params()[0]));
    if (channel->is_user_OP(user))
    {
        std::cout << "sexcasst " << std::endl;
        channel->set_topic(message.get_params()[1]);
        channel->broadcast(bld_rpl_topic_msg(user ,*channel), NULL); 
    }


}
// void whois_handler(User &user, Message const &message, ServerCore &core) {}
void privmsg_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager *_chanel_man = &core.get_channelManager();
    std::string message_;
    // std::cout << "errferfe " << user.get_nickname() << std::endl;
    if (message.get_params().size() < 1)
    {
        user.send_messsage("412 :No text to send");
        return;
    }
    for (int i = 1; i < (int)message.get_params().size(); i++)
    {
        message_ += message.get_params()[i];
    }
    if (message.get_params()[0][0] == '#' || message.get_params()[0][0] == '&')
    {
        Channel *channel = _chanel_man->get_channel(message.get_params()[0]);
        std::cout << message.get_params()[0] << std::endl;
        if (!channel)
        {
            user.send_messsage(bld_err_nosuchchannel(message.get_params()[0]));
            return ;
        }
        if (!channel->is_user_present(user.get_nickname()))
        {
            user.send_messsage(bld_err_notonchannel(*channel));
            return ;
        }
        channel->broadcast(bld_privmsg_msg(user, *channel, message_), &user);
    }
    else
    {
        UserManager *user_man = &core.get_userManager();
        User *recipient_user = user_man->get_user(message.get_params()[0]);
        // std::cout << bld_err_nosuchnick(message.get_params()[0]) << std::endl;
        if (recipient_user == NULL)
            user.send_messsage(bld_err_nosuchnick(message.get_params()[0]), false);
        else
            recipient_user->send_messsage(bld_privmsg_msg(user, *recipient_user, message_), false);
    }
}