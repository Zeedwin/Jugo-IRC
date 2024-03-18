#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "User.h"
#include "message_builder.h"

User::User(int fd) : _fd(fd){}

User User::operator=(const User &rhs) const {
    return(*this);
}

int User::is_me(int fd) const
{
    if (this->_fd != fd)
        return(0);
    return(1);
}

int User::is_me(std::string const &nickname) const
{
    if (this->_nickname != nickname)
        return (0);
    return(1);
}

int User::is_state(user_state_t state) const
{
    if (this->_state != state)
        return (0);
    return(1);
}

int User::check_flag(int flag) const {
    return(0);
}

void	User::set_flag(int flag, int set_to){}

void    User::set_state(user_state_t state){
    this->_state = state;
}
#include <iostream>
void    User::set_nickname(std::string const &nickname){
    this->_nickname = nickname;
}

void    User::set_user(std::string const &username, std::string const &hostname, std::string const &servername, std::string const &realname){
    this->_username = username;
    this->_hostname = hostname;
    this->_servername = servername;
    this->_realname = realname;
    this->_prefix = this->_nickname + "!" + this->_username + "@" + this->_hostname;
}

void     User::set_last_pong(void){}

void     User::set_last_ping(void){}

const std::string & User::get_nickname(void)   const{
    return(this->_nickname);
}

const std::string & User::get_username(void)   const{
    return(this->_username);
}

const std::string & User::get_hostname(void)   const{
    return(this->_hostname);
}

const std::string & User::get_servername(void) const{
    return(this->_servername);
}

const std::string &User::get_realname(void)   const{
    return(this->_realname);
}

const std::string &User::get_prefix(void)     const{
    return(this->_prefix);
}

/*const std::string  User::get_mode(void)        const{
    return(this->_mode)
}*/

time_t             User::get_last_ping(void)   const{
    return(this->_last_ping);
}

//time_t             User::get_delta(void)       const{}

int     User::send_messsage(std::string const &message, bool throw_exception){
    return(send(this->_fd, message.c_str(), message.size(), MSG_DONTWAIT | MSG_NOSIGNAL));
}

void    User::recvu(void){
    char buff[513];
    ssize_t ret = recv(this->_fd, buff, 512, MSG_DONTWAIT | MSG_NOSIGNAL);
    if (ret <= 0) {
        // TODO:
    } else {
        buff[ret] = 0;
        this->_buffer += buff;
    }
}

int     User::is_message_buffered(void){
    for (int i = 0; i <= this->_buffer.size(); i++)
    {
        if (this->_buffer[i] == '\r' && this->_buffer[i + 1] == '\n')
        {
            return(1);
        }
    }
    return(0);
}

void    User::get_message(Message &msg){
    size_t oc = this->_buffer.find("\r\n");
    std::string str;
    str = this->_buffer.substr(0, oc);
    this->_buffer.erase(0, oc + 2);
    msg.update(str);
}

void    User::send_ping(void){}

void	User::set_idle(void){

}

//time_t	User::get_idle(void) const {}

void	User::close_connection(void){}

User::~User(void){
    
}