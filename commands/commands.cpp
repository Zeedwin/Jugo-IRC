#include "commands.h"
#include <iostream>
#include "../message_builder.h"
void cap_handler(User &user, Message const &message, ServerCore &core){}
void pass_handler(User &user, Message const &message, ServerCore &core)
{
    if (core.get_password() != message.get_params()[0])
    {
        std::cout << "non ono non" << std::endl;
        user.set_state(User::WAITING_FOR_QUIT);
    }
    else
        user.set_state(User::WAITING_FOR_CONN_1);
}
void nick_handler(User &user, Message const &message, ServerCore &core)
{
    user.set_nickname(message.get_params()[0]);
    user.set_state(User::WAITING_FOR_CONN_2);

}
void user_handler(User &user, Message const &message, ServerCore &core)
{
    std::cout << "user_handler" << std::endl;
    user.set_user(message.get_params()[0], message.get_params()[1], message.get_params()[2], message.get_params()[3]);
    user.set_state(User::CONNECTED);
    user.send_messsage(bld_rpl_welcome(user), true);
}
void mode_handler(User &user, Message const &message, ServerCore &core){}
void join_handler(User &user, Message const &message, ServerCore &core){}
void part_handler(User &user, Message const &message, ServerCore &core){}
void quit_handler(User &user, Message const &message, ServerCore &core){}
void pong_handler(User &user, Message const &message, ServerCore &core){}
void ping_handler(User &user, Message const &message, ServerCore &core){}
void kick_handler(User &user, Message const &message, ServerCore &core){}
void topic_handler(User &user, Message const &message, ServerCore &core){}
void whois_handler(User &user, Message const &message, ServerCore &core){}
void privmsg_handler(User &user, Message const &message, ServerCore &core){}