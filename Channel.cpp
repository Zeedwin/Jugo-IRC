#include "Channel.h"
#include "message_builder.h"
#include <iostream>
Channel::Channel(std::string const &channel_name) : channel_name(channel_name) {

}

bool Channel::operator==(Channel const &channel)
{
    return this->channel_name == channel.channel_name;
}

int Channel::is_me(std::string const &channel_name)
{
    return this->channel_name == channel_name;
}

std::string const &Channel::get_name(void) const
{
    return this->channel_name;
}

std::string const &Channel::get_topic(void) const
{
    return this->topic;
}

int Channel::join(User &user){
    this->members.push_back(&user);
    this->broadcast(bld_join_msg(user, *this), NULL);
    return 0;
}

int Channel::quit(User &user)
{
    // for (int i = 0; i < this->members.size(); i++) {
    //     if ((this->members[i].get_nickname() == user.get_nickname())) {
    //         std::cout << "User " << user.get_nickname() << " left channel " << this->channel_name << std::endl;
    //         continue;
    //     }
    //     std::cout << " remains " <<  this->members[i].get_nickname() << std::endl;
    //     tmp.push_back(this->members[i]);
    // }

    // this->members = tmp;
    
    for (std::vector<User*>::iterator it = this->members.begin(); it < this->members.end(); it++)
    {
        if (user.get_nickname() == (*it)->get_nickname())
        {
            std::cout << "User " << (*it)->get_nickname() << " left channel " << this->channel_name << std::endl;
            //this->broadcast(bld_part_msg(user, *this), &user);
            this->members.erase(it);
            break;
        }
    }
    for (std::vector<User*>::iterator it2 = this->members.begin(); it2 < this->members.end(); it2++)
    {
        std::cout << "THIS USER IS CONNECTED STILL: " << (*it2)->get_nickname() << std::endl;
    }
    return (0);
}

int Channel::kick(User &kicker, User &kicked, std::string const &reason)
{
    for (std::vector<User*>::iterator it = this->members.begin(); it < this->members.end(); it++)
    {
        if (kicked.get_nickname() == (*it)->get_nickname())
        {
            std::cout << "User " << (*it)->get_nickname() << " left channel " << this->channel_name << std::endl;
            this->broadcast(bld_kick_msg(kicker, kicked, *this, reason), NULL);
            this->members.erase(it);
            break;
        }
    }
    return 0;
}

void Channel::set_channel()
{
}

void Channel::set_topic(std::string const &topic){
    this->topic = topic;
}

void Channel::set_topic_changer(const User &user)
{
}

int Channel::add_OP(User &user){
    this->OPs.push_back(&user);
    return 0;
}

int Channel::remove_OP(const User &user)
{
    return 0;
}

int Channel::remove_user(User &user)
{
    return 0;
}

// int Channel::is_user_present(User const &user){

// }

int Channel::is_user_present(std::string const &nickname)
{
    for (std::vector<User*>::iterator it = this->members.begin(); it < this->members.end(); it++)
    {
        if ((*it)->get_nickname() == nickname)
        {
            //std::cout << nickname << " is in " << this->channel_name << std::endl;
            return 1;
        }
    }
    //std::cout << nickname << "is not in " << this->channel_name << std::endl;
    return 0;
}

int Channel::is_user_OP(User const &user) const{
    for (int i = 0; i < this->OPs.size(); i++)
    {
        if(*this->OPs[i] == user)
        {
            return (1);
        }
    }
    return 0;
}

int Channel::is_user_OP(std::string const &nickname) const{
    for (int i = 0; i < this->OPs.size(); i++)
    {
        if(this->OPs[i]->is_me(nickname) == 1)
        {
            return (1);
        }
    }
    return 0;
}

int Channel::broadcast(std::string const &message, const User *from_user){
    for (int i = 0; i < this->members.size(); i++)
    {
        //std::cout << "il envoie = " << from_user->get_nickname() << std::endl;
        //std::cout << "membre = " << this->members[i]->get_nickname() << std::endl;
        if (this->members[i] == from_user)
        {
            std::cout << "on est dans le print" << std::endl;
            continue;
        }
        this->members[i]->send_messsage(message, false);
    }
    return 0;
}

size_t Channel::members_count(void) const
{
    for (size_t i = 0; i < this->members.size(); i++)
    {
        if (i == this->members.size())
            return (i);
    }
}

const std::string Channel::get_username_list(void) const{

    
    return "mafoi\n";
}
