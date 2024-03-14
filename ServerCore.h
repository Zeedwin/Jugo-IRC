#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include "ChannelManager.h"
#include "UserManager.h"

class ServerCore
{
    private:
        std::string const   password;
        ChannelManager      channel_manager;
        UserManager         user_manager;

		void				disconnect_clients(std::vector<pollfd_t> &poll_fds);

    public:
        ServerCore(std::string const &password);

        const std::string &get_password(void) const;
        ChannelManager    &get_channelManager(void);
        UserManager       &get_userManager(void);

        void    loop(int listen_port); /* methode utilisée pour lancer le serveur (là où y'a le poll (2)) */

        ~ServerCore(void);
};

#endif