#include <iostream>
#include "command_handler.h"

struct {
    std::string cmd;
    User::user_state_t state_needed;
    int min_arg;
    int max_arg;
    void *handle;
}  command_table[] = {
    // {.cmd = "PASS", .state_needed = User::WAITING_FOR_PASS, .min_arg = 1, .max_arg = 1, .handle = handle_pass},
    // {.cmd = "NICK", .state_needed = User::WAITING_FOR_PASS, .min_arg = 1, .max_arg = 1, .handle = handle_nick},
    // {.cmd = "USER", .state_needed = User::WAITING_FOR_PASS, .min_arg = 1, .max_arg = 1, .handle = handle_user},

};

int check_command(User &user, Message &message) {


}

void handle_command(User &user, Message const &message, ServerCore &core)
{
    const std::vector<std::string> & para = message.get_params();

    //std::cout << "raw=" 
    std::cout << "LEN=" << para.size() << std::endl;
    std::cout << message.get_command() << "|";
    for (int i = 0; i < para.size(); i++)
    {
        std::cout << para[i] << "|"; 
    }
    std::cout << std::endl;
}