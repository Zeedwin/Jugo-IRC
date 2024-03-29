#include "ChannelManager.h"
#include "message_builder.h"
#include <iostream>
#include "defines.h"

ChannelManager::ChannelManager(void){
    
}
Channel  *ChannelManager::get_channel(std::string const &name){
    // TODO: pas cast size en int mais changer type i en size-t
    for (size_t i = 0; i < channels.size(); i++)
    {
        if(channels[i]->is_me(name))
        {
            return channels[i];
        }
    }
    return NULL;
}
int     ChannelManager::create(User &user, std::string const &chan_name){
    Channel *disney = new Channel(chan_name);
    std::cout << "NEW CHANNEL " << chan_name << std::endl;
    this->channels.push_back(disney);
    disney->add_OP(user);
    disney->set_flags(MODE_t);
    disney->join(user);
    return 0;
}
void    ChannelManager::leave(User &user, std::string const message){
    for (int i = 0; i < (int)channels.size(); i++)
    {
            std::cout << "COUSCOUS A LA MAISON " << this->channels[i]->is_user_present(user.get_nickname()) << std::endl;
        if (this->channels[i]->is_user_present(user.get_nickname()) == 0)
        {

            this->channels[i]->quit(user, message);
            //todo: destroy channel if empty & remove OP(discord mod privileges(dont post jb in #general use #jailbait))
        }
    }
    
}   
void    ChannelManager::leave(User &user, Channel &chan, std::string const message){
    chan.quit(user, message);
    //std::cout << "COUSCOUS A LA MAISON" << std::endl;
    //todo: destroy channel if empty & remove OP(discord mod privileges(dont post jb in #general use #jailbait))
}
