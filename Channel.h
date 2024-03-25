#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <string>
#include <vector>

#include "User.h"

class Channel
{
    private:
        std::string   		channel_name;
        std::string         topic;
        std::vector<User*>   members;
        std::vector<User*>   OPs;
        const User          *topic_changer;
        
    public:
        Channel(std::string const &channel_name);

        bool operator==(Channel const &channel);

        int is_me(std::string const &channel_name);

        std::string const &get_name(void)  const;
        std::string const &get_topic(void) const;

        int join(User &user);
        int quit(User &user);
        int kick(User &kicker, User &kicked, std::string const &reason);

        void set_channel();
        void set_topic(std::string const &topic);
        void set_topic_changer(const User &user);

        int add_OP(User &user);
        int remove_OP(const User &user);

		int remove_user(User &user);

        int is_user_present(User const &user);
        int is_user_present(std::string const &nickname);

        int is_user_OP(User const &user) const;
        int is_user_OP(std::string const &nickname) const;

        int broadcast(std::string const &message, const User *from_user);

		size_t members_count(void) const;
		const std::string get_username_list(void) const;

        ~Channel(void){
            
        };
};

#endif
