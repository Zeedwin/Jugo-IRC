#include ¨User.h¨

User::User(int fd) : _fd(fd){}

User &User::operator=(const User &rhs) const {
    return(*this);
}

int User::is_me(int fd)
{
    if (this->_fd != fd)
        return(0);
    return(1);
}

int User::is_me(std::string const &nickname)
{
    if (this->nickname != nickname)
        return (0);
    return(1);
}

int User::is_state(user_state_t state) const
{
    if (this->state != state)
        return (0);
    return(1);
}

int User::check_flag(int flag) const {

}

void	User::set_flag(int flag, int set_to){}

void    User::set_state(user_state_t state){
    this->state = state;
}

void    User::set_nickname(std::string const &nickname){}

void    User::set_user(std::string const &username, std::string const &hostname, std::string const &servername, std::string const &realname){}

void     User::set_last_pong(void){}

void     User::set_last_ping(void){}


const std::string & User::get_nickname(void)   const{}

const std::string & User::get_username(void)   const{}

const std::string & User::get_hostname(void)   const{}

const std::string & User::get_servername(void) const{}

const std::string &User::get_realname(void)   const{}

const std::string &User::get_prefix(void)     const{}

const std::string  User::get_mode(void)        const{}

time_t             User::get_last_ping(void)   const{}

time_t             User::get_delta(void)       const{}

int     User::send_messsage(std::string const &message, bool throw_exception=true){}

void    User::recvu(void){}

int     User::is_message_buffered(void){}

void    User::get_message(Message &msg){}

void    User::send_ping(void)

void	User::set_idle(void){}

time_t	User::get_idle(void) const {}

void	User::close_connection(void){}

User::~User(void){}