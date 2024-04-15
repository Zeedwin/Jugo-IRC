#include <iostream>
#include <string>
#include <unistd.h>
#include "command_handler.h"
#include "commands/commands.h"
#include "message_builder.h"

struct command_table
{
    std::string cmd;
    User::user_state_t state_needed;
    int min_arg;
    int max_arg;
    void (*handle)(User &, Message const &, ServerCore &);

};

struct command_table static const command_table[] = {
    {.cmd = "PASS",    .state_needed = (User::user_state_t)-1, .min_arg = 1, .max_arg = 1, .handle = pass_handler},
    {.cmd = "NICK",    .state_needed = (User::user_state_t)-1, .min_arg = 1, .max_arg = 1, .handle = nick_handler},
    {.cmd = "USER",    .state_needed = (User::user_state_t)-1, .min_arg = 4, .max_arg = 4, .handle = user_handler},
    {.cmd = "JOIN",    .state_needed = User::CONNECTED,        .min_arg = 1, .max_arg = -1,.handle = join_handler},
    {.cmd = "PART",    .state_needed = User::CONNECTED,        .min_arg = 1, .max_arg = 2, .handle = part_handler},
    {.cmd = "PRIVMSG", .state_needed = User::CONNECTED,        .min_arg = 1, .max_arg =-1, .handle = privmsg_handler},
    {.cmd = "PING",    .state_needed = (User::user_state_t)-1, .min_arg = 1, .max_arg = 2, .handle = ping_handler},
    {.cmd = "PONG",    .state_needed = (User::user_state_t)-1, .min_arg = 0, .max_arg = 2, .handle = pong_handler},
    {.cmd = "TOPIC",   .state_needed = (User::CONNECTED),      .min_arg = 1, .max_arg = 2, .handle = topic_handler},
    {.cmd = "KICK",    .state_needed = User::CONNECTED,        .min_arg = 1, .max_arg = -1,.handle = kick_handler},
    {.cmd = "MODE",    .state_needed = User::CONNECTED,        .min_arg = 1, .max_arg = -1,.handle = mode_handler},
    {.cmd = "INVITE",  .state_needed = (User::CONNECTED),      .min_arg = 2, .max_arg = 2, .handle = invite_handler},
    {.cmd = "CAP",     .state_needed = (User::CONNECTED),      .min_arg = 0, .max_arg = -1,.handle = cap_handler},
    {.cmd = "WHOIS",   .state_needed = (User::CONNECTED),      .min_arg = 0, .max_arg = 2, .handle = whois_handler},
    {.cmd = "QUIT",    .state_needed = (User::CONNECTED),      .min_arg = 1, .max_arg = 2, .handle = quit_handler}
 };

int check_command(User &user, Message const &message, int i, ServerCore &core)
{
    (void)core;
    std::vector<std::string> const &vector = message.get_params();
    if (!user.is_state(command_table[i].state_needed) && command_table[i].state_needed != (User::user_state_t)-1)
    {
        std::cout << " 11111111111111" << std::endl;
        return (0);
    }
    if ((int)vector.size() < command_table[i].min_arg)
    {
        std::cout << " 111111122221111" << std::endl;
        return (2);
    }
    if ((ssize_t)(vector.size()) > (ssize_t)command_table[i].max_arg && (ssize_t)command_table[i].max_arg >= 0)
    {
        std::cout << "waaaaw" << std::endl;
        return (0);
    }
    return (1);
}

void handle_command(User &user, Message const &message, ServerCore &core)
{
    std::cout << "command = " << message.get_command()<< "," << message.get_params().size() << std::endl;
    for (unsigned long index = 0; index < sizeof(command_table) / sizeof(command_table[0]); index++)
    {
        if (message.get_command() == command_table[index].cmd && check_command(user, message, index, core) == 1)
        {
             std::cout << "on lrentre dedans" << std::endl;
            command_table[index].handle(user, message, core);
            return;
        }
        else if (message.get_command() == command_table[index].cmd && check_command(user, message, index, core) == 2)
        {
            user.send_message(bld_err_needmoreparams(message.get_command(), user), false);
            return;
        }
    }
    std::cout<< " commad = " << message.get_command() << std::endl;
    user.send_message(bld_err_unknowncmd(message.get_command()));
    // std::cout << "user = " << user.get_username() << std::endl;
}