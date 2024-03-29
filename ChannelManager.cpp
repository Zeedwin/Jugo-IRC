#include "ChannelManager.h"
#include "message_builder.h"
#include <iostream>
#include "defines.h"

ChannelManager::ChannelManager(void){
    
}
Channel  *ChannelManager::get_channel(std::string const &name){
    for (int i = 0; i < (int)channels.size(); i++)
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
        chan->add_OP(user);
        chan->set_flags(MODE_t);
        std::cout << "NEW CHANNEL " << chan_name << std::endl;
    }
    chan->join(user);
    user.send_messsage(bld_rpl_topic(*chan));
    user.send_messsage(bld_rpl_namreply(*chan));
    // user.send_messsage(bld_join_msg(user, *chan), true);
    return 0;
}
void    ChannelManager::leave(User &user, std::string const message){
    for (int i = 0; i < (int)channels.size(); i++)
    {
            std::cout << "COUSCOUS A LA MAISON " << this->channels[i].is_user_present(user.get_nickname()) << std::endl;
        if (this->channels[i].is_user_present(user.get_nickname()) == 0)
        {

            this->channels[i].quit(user, message);
            //todo: destroy channel if empty & remove OP(discord mod privileges(dont post jb in #general use #jailbait))
        }
    }
    
}   
void    ChannelManager::leave(User &user, Channel &chan, std::string const message){
    chan.quit(user, message);
    //std::cout << "COUSCOUS A LA MAISON" << std::endl;
    //todo: destroy channel if empty & remove OP(discord mod privileges(dont post jb in #general use #jailbait))
}
