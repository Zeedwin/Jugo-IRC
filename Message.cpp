#include "Message.h"

Message::Message(void){}

Message::Message(std::string const &raw_message){
}

void Message::update(const std::string &raw_message){
    int i = 0;
    if (raw_message[i] == ':')
    {
        i = raw_message.find(' ');
    }
    this->command = raw_message.substr(++i, raw_message.find(' '));
    i = raw_message.find(' ');
    i++;
    int j = 0;
    while (i < raw_message.size())
    {
        if(raw_message[i] != ':')
        {
            this->params[j] = raw_message.substr(++i, raw_message.find(' '));
            i = raw_message.find(' ');
        }
        else
        {
            this->params[j] = raw_message.substr(++i + 1, raw_message.size());
            i = raw_message.size();
        }
        j++;
    }
}

std::string const &Message::get_command(void) const{
    return (this->command);
}

std::vector<std::string> const &Message::get_params(void)  const{
    return(this->params);
}

Message::~Message(void){}