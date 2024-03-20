#include "ChannelManager.h"
#include "message_builder.h"
#include <iostream>

ChannelManager::ChannelManager(void){
    
}
Channel  *ChannelManager::get_channel(std::string const &name){
    for (int i = 0; i < channels.size(); i++)
    {
        if(channels[i].is_me(name))
        {
            return &channels[i];
        }
    }
    return NULL;
}
int     ChannelManager::join(User &user, std::string const &chan_name){
    Channel *chan = this->get_channel(chan_name);
    if (chan == NULL) {
        Channel disney(chan_name);
        this->channels.push_back(disney);
        chan = this->get_channel(chan_name);
        //std::cout << "name = " << chan_name << std::endl;
        disney.add_OP(user);
    }
    chan->join(user);
    user.send_messsage(bld_join_msg(user, *chan), true);
    return 0;
}
void    ChannelManager::leave(User &user){
    for (int i = 0; i < channels.size(); i++)
    {
        if (channels[i].is_user_present(user.get_nickname()))
        {
            channels[i].quit(user);
            //todo: destroy channel if empty & remove OP(discord mod privileges(dont post jb in #general use #jailbait))
        }
    }
    
}   
void    ChannelManager::leave(User &user, Channel &chan){
    chan.quit(user);
    //todo: destroy channel if empty & remove OP(discord mod privileges(dont post jb in #general use #jailbait))
}
