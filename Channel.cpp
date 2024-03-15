#include "Channel.h"

Channel::Channel(std::string const &channel_name){

}

bool Channel::operator==(Channel const &channel){

}

int Channel::is_me(std::string const &channel_name){

}

std::string const &Channel::get_name(void)  const
{

}

std::string const &Channel::get_topic(void) const{

}

int Channel::join(User &user){

}

int Channel::quit(User &user){

}

int Channel::kick(User &kicker, User &kicked, std::string const &reason){

}

void Channel::set_channel(){

}

void Channel::set_topic(std::string const &topic){

}

void Channel::set_topic_changer(const User &user){

}

int Channel::add_OP(User &user){

}

int Channel::remove_OP(const User &user){

}

int Channel::remove_user(User &user){

}

int Channel::is_user_present(User const &user){

}

int Channel::is_user_present(std::string const &nickname){

}

int Channel::is_user_OP(User const &user) const{

}

int Channel::is_user_OP(std::string const &nickname) const{

}

int Channel::broardcast(std::string const &message, const User *from_user){

}

size_t Channel::members_count(void) const{

}

const std::string Channel::get_username_list(void) const{

}
