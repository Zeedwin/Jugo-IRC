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
        std::string         key;
        int flags;
        int user_limit;
        
    public:
        Channel(std::string const &channel_name);

        bool operator==(Channel const &channel);

        int is_me(std::string const &channel_name);

        std::string const &get_name(void)  const;
        std::string const &get_topic(void) const;
        std::string const &get_key(void) const;
        int const &get_userlimit(void) const;

        int join(User &user);
        int quit(User &user, std::string const message);
        int kick(User &kicker, User &kicked, std::string const &reason);

        void set_userlimit(int i);
        void set_channel();
        void set_key(std::string str);
        void set_topic(std::string const &topic);
        void set_topic_changer(const User &user);
        void set_flags(int flag);
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
        int get_flag(int flag);
        int remove_flag(int flag);

        ~Channel(void){
            
        };
};

#endif
