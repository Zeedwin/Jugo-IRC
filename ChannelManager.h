#ifndef CHANNEL_MANAGER_H_
#define CHANNEL_MANAGER_H_

#include <string>
#include <vector>

#include "Channel.h"

class ChannelManager
{
    private:
        std::vector<Channel>    channels;

    public:
        ChannelManager(void);

        Channel  *get_channel(std::string const &name); /* algorithm + find_if ? */
        
        void    leave(User &user); /* quitte tous les salons */
        void    leave(User &user, Channel &chan); /* quitte un salon spécifiquement */

        /*  rejoin le salon `chan_name` (en créant le salon + OP s'il n'existe pas),
            retourne 0 en cas de succès ou le numéro d'erreur associé au message `JOIN` en cas d'erreur */
        int     join(User &user, std::string const &chan_name);
        
        ~ChannelManager(void){
            
        };
};

#endif
