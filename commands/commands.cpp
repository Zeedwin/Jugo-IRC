#include "commands.h"
#include <iostream>
#include "../message_builder.h"
#include "../Channel.h"
#include "../User.h"
#include "../UserManager.h"
#include "../ServerCore.h"
#include <string> 
#include <algorithm>
#include <vector>
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

// void cap_handler(User &user, Message const &message, ServerCore &core)
// {
//     return;
// }

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
    (void)user;
    (void)core;
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
    std::string chans = message.get_params()[0];
    std::string keys = "";
    while(chans.size() > 0)
    {
        std::string cha_name = get_arg(chans);
        Channel *chan = _chanel_manager.get_channel(cha_name);
        if (message.get_params().size() > 1 && chan != NULL)
            keys = message.get_params()[1];
        if(chans.find(',') != std::string::npos)
        {
            chans = chans.substr(chans.find(',') + 1, chans.size() - chans.find(','));
        }
        else
            chans = "";
        if (chan == NULL)
        {
            _chanel_manager.create(user, cha_name);
        }
        else if (chan->get_key() != "")
        {
            std::string key = get_arg(keys);
            if (keys.find(',') != std::string::npos)
            {
                keys = keys.substr(keys.find(',') + 1, keys.size() - keys.find(','));
            }
            else{
                keys = "";
            }
            if (key == chan->get_key())
            {
                if (chan->is_on_invite())
                {
                    if (chan->is_user_invited(user))
                        chan->join(user);
                    else
                    {}
                        //todo bld err
                }
                else
                    chan->join(user);
            }
            else
            {
                user.send_messsage(bld_err_badchannelkey(chan->get_name()));
            }
        }
        else if (chan->get_key() == "")
        {
                if (chan->is_on_invite())
                {
                    if (chan->is_user_invited(user))
                        chan->join(user);
                    else
                    {}
                        //todo bld err
                }
                else
                    chan->join(user);
        }
    }
}
int check_mode(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] != 'i' && str[i] != 'k' && str[i] != 'o' && str[i] != 'l' && str[i] != 't' && str[i] != '+' && str[i] != '-')
            return (0);
    }
    return (1);
}

int remaining_mode(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == 'i' || str[i] == 'k' || str[i] == 'o' || str[i] == 'l' || str[i] == 't')
            return (1);
    }
    return (0);
}

void mode_handler(User &user, Message const &message, ServerCore &core) {
    
    (void)user;    
    std::string str = message.get_params()[1];
    int i = 1;
    int k = 2;
    std::cout << message.get_command() << " " << message.get_params()[0] << message.get_params()[1] <<  std::endl;
    UserManager    &user_man = core.get_userManager();
    ChannelManager &chan_man = core.get_channelManager();
    Channel *chan = chan_man.get_channel(message.get_params()[0]);
    if (message.get_params()[0][0] != '#' && message.get_params()[0][0] != '&')
        return;
    if (check_mode(message.get_params()[1]) == 0)
        return;
    while(remaining_mode(str) == 1)
    {
        for (size_t j = 0; j < str.size(); j++)
        {
            if (str[j] == '+')
                i = 1;
            if (str[j] == '-')
                i = -1;
            if (str[j] == 'k')
            {
                if (i == 1)
                {
                    chan->set_flags(MODE_k);
                    chan->set_key(message.get_params()[k]);
                }
                if (i == -1 && chan->get_key() == message.get_params()[k])
                {
                    chan->remove_flag(MODE_k);
                    chan->set_key("");
                }
                k++;
                str = str.substr(j + 1, str.size() - j);
                break;
            }
            if (str[j] == 'o')
            {
                User *user = user_man.get_user(message.get_params()[k]);
                if (i == 1)
                {
                    chan->add_OP(*user);
                }
                if (i == -1)
                {
                    chan->remove_OP(*user);
                }
                k++;
                str = str.substr(j + 1, str.size() - j);
                break;
            }
            if (str[j] == 'i')
            {
                if (i == 1)
                    chan->set_flags(MODE_i);
                if (i == -1)
                    chan->remove_flag(MODE_i);
                str = str.substr(j + 1, str.size() - j);
                break;
            }
            if (str[i] == 't')
            {
                if (i == 1)
                    chan->set_flags(MODE_t);
                if (i == -1)
                    chan->remove_flag(MODE_t);
                str = str.substr(j + 1, str.size() - j);
                break;
            }
            if (str[i] == 'l')
            {
                if (i == 1)
                {
                    chan->set_userlimit(atoi(message.get_params()[k].c_str()));
                    chan->set_flags(MODE_l);
                    k++;
                }
                if (i == -1)
                {
                    chan->set_userlimit(-1);
                    chan->remove_flag(MODE_l);
                }
                str = str.substr(j + 1, str.size() - j);
                break;
            }
        }
    }
}
void part_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager &_chan_man = core.get_channelManager();
    std::string message_;
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

// TODO: void quit_handler(User &user, Message const &message, ServerCore &core) {}

void pong_handler(User &user, Message const &message, ServerCore &core)
{
    (void)message;
    (void)core;
    user.set_last_pong();
}
void ping_handler(User &user, Message const &message, ServerCore &core)
{
    (void)core;
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
            user.send_messsage(bld_err_nosuchchannel(chans), false);
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
    if (!channel)
        user.send_messsage(bld_err_nosuchchannel(message.get_params()[0]));
    else if(!channel->is_user_present(user.get_nickname()))
        bld_err_notonchannel(channel->get_name());
    //else if (channel->get_topic_changer().empty())
    //     user.send_messsage(bld_rpl_notopic(*channel));
    else if (channel->is_user_OP(user))
    {
        if (message.get_params().size() == 2) {
            channel->set_topic_changer(user);
            channel->set_topic(message.get_params()[1]);
            channel->broadcast(bld_rpl_topic_msg(user ,*channel, true), NULL);
        }
        else{
            user.send_messsage(bld_rpl_topic(*channel, channel->get_topic_changer()));
            user.send_messsage(bld_rpl_topic_changer(*channel));
        }
    }
    else
    {
        if(message.get_params().size() == 2)
            user.send_messsage(bld_err_chanoprivsneeded(*channel));
        else
          user.send_messsage((bld_rpl_topic(*channel, user.get_nickname())));
       // channel->broadcast(bld_rpl_topic_msg(user, *channel), &user);
    }
}
// void whois_handler(User &user, Message const &message, ServerCore &core) {}
void privmsg_handler(User &user, Message const &message, ServerCore &core)
{
    ChannelManager &_chanel_man = core.get_channelManager();
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
        Channel *channel = _chanel_man.get_channel(message.get_params()[0]);
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

void invite_handler(User &user, Message const &message, ServerCore &core){
    ChannelManager &_chanel_man = core.get_channelManager();
    Channel   *chan = _chanel_man.get_channel(message.get_params()[1]);
    UserManager &userman =core.get_userManager();
     std::cout << message.get_params()[1] << std::endl;
    
    if (chan == NULL) {
    std::cout << "uno" << std::endl;
        user.send_messsage(bld_err_nosuchchannel(message.get_params()[1]), false);
        return;
    }
    std::cout << "dos" << std::endl;

    if (!chan->is_user_OP(user)) {
        user.send_messsage(bld_err_chanoprivsneeded(*chan));
        return;
    }
    std::cout << "tres" << std::endl;
    User *invd = userman.get_user(message.get_params()[0]);
    if (invd == NULL) {
        user.send_messsage(bld_err_nosuchnick(message.get_params()[0]), false);
        return;
    }
    chan->invite(user, invd);
    std::cout << "cuatro" << std::endl;
}
