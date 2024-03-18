#include <iostream>
#include <string>
#include "command_handler.h"
#include "commands/commands.h"

struct {
    std::string cmd;
    User::user_state_t state_needed;
    int min_arg;
    int max_arg;
    void (*handle)(User &, Message const &, ServerCore &);

}  command_table[] = {
     {.cmd = "PASS", .state_needed = User::WAITING_FOR_PASS, .min_arg = 1, .max_arg = 1, .handle = pass_handler},
     {.cmd = "NICK", .state_needed = User::WAITING_FOR_CONN_1, .min_arg = 1, .max_arg = 1, .handle = nick_handler},
     {.cmd = "USER", .state_needed = User::WAITING_FOR_CONN_2, .min_arg = 4, .max_arg = 4, .handle = user_handler},
     {.cmd = "NICK", .state_needed = User::CONNECTED, .min_arg = 1, .max_arg = 1, .handle = nick_handler},
     {.cmd = "JOIN", .state_needed = User::CONNECTED, .min_arg = 1, .max_arg = 1, .handle = join_handler},
     {.cmd = "PART", .state_needed = User::CONNECTED, .min_arg = 1, .max_arg = 1, .handle = part_handler},

};

int check_command(User &user, Message const &message, int i, ServerCore &core) {
    std::vector<std::string> const &vector = message.get_params();

    if (!user.is_state(command_table[i].state_needed))
        return(0);
    if (vector.size() < command_table[i].min_arg)
        return (0);
    if (vector.size() > command_table[i].max_arg)
        return (0);
    return(1);

}

void handle_command(User &user, Message const &message, ServerCore &core)
{
    for (int index = 0; index < sizeof(command_table) / sizeof(command_table[0]); index++)
    {
        if (message.get_command() == command_table[index].cmd && check_command(user, message, index, core))
        {
            command_table[index].handle(user, message, core);
        }
    }
    //std::cout << "user = " << user.get_username() << std::endl;
}