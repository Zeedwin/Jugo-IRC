#include "Channel.h"

Channel::Channel(std::string const &channel_name){

}

bool Channel::operator==(Channel const &channel){
    return this->channel_name == channel.channel_name;
}

int Channel::is_me(std::string const &channel_name){
    return this->channel_name == channel_name;
}

std::string const &Channel::get_name(void)  const
{
    return this->channel_name;
}

std::string const &Channel::get_topic(void) const{
    return this->topic;
}

int Channel::join(User &user){
    return 0;
}

int Channel::quit(User &user){
    return 0;
}

int Channel::kick(User &kicker, User &kicked, std::string const &reason){
    return 0;
}

void Channel::set_channel(){

}

void Channel::set_topic(std::string const &topic){

}

void Channel::set_topic_changer(const User &user){

}

int Channel::add_OP(User &user){
    return 0;
}

int Channel::remove_OP(const User &user){
    return 0;
}

int Channel::remove_user(User &user){
    return 0;
}

int Channel::is_user_present(User const &user){
    return 0;
}

int Channel::is_user_present(std::string const &nickname){
    return 0;
}

int Channel::is_user_OP(User const &user) const{
    return 0;
}

int Channel::is_user_OP(std::string const &nickname) const{
    return 0;
}

int Channel::broardcast(std::string const &message, const User *from_user){
    return 0;
}

size_t Channel::members_count(void) const{
    return 0;
}

const std::string Channel::get_username_list(void) const{
    return "mafoi\n";
}
