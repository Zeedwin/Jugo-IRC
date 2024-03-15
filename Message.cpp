#include "Message.h"

Message::Message(void){}

Message::Message(std::string const &raw_message){
    this->command = raw_message;
    for (int i = 0; raw_message[i] != '\n' && raw_message[i + 1] != '\r'; i++)
    {
        this->command[i] = raw_message[i];
    }
}

void Message::update(const std::string &raw_message){}

std::string const &Message::get_command(void) const{
    return (this->command);
}

std::vector<std::string> const &Message::get_params(void)  const{
    return(this->params);
}

Message::~Message(void){}