#include "User.h"
#include "UserManager.h"
#include "ServerCore.h"
#include "message_builder.h"

#define SUS "Welcome to Jugo's IRC Server"

#define BADPASS "Bad password"

#define NOPASS "NO PASSWORD WTF VRO"

const std::string bld_privmsg_msg(const User &usr, const Channel &chn, const std::string &msg) {
    return( ":" + usr.get_prefix() + " PRIVMSG " + chn.get_name() + " :" + msg + "\r\n");
}
const std::string bld_privmsg_msg(const User &usr, const User &target, const std::string &msg) {
    return "Hello brother";
}

const std::string bld_rpl_topic(const Channel &chan){
    return "lmao";
}
const std::string bld_rpl_welcome(const User &user){
    return  "001 " + user.get_nickname() + " :Welcome to the Internet Relay Network " + user.get_nickname() + "!" + user.get_username() + "@" + user.get_hostname() + "\r\n";
}
const std::string bld_rpl_umodeis(const User &user){
    return "lmao";
}
const std::string bld_rpl_notopic(const Channel &chan){
    return "lmao";
}
const std::string bld_rpl_whoisuser(const User &user){
    return "lmao";
}
const std::string bld_rpl_whoisoperator(const User &user){
    return "lmao";
}
const std::string bld_rpl_endofwhois(const User &user){
    return "lmao";
}
const std::string bld_rpl_namreply(const Channel &chan){
    return "lmao";
}
const std::string bld_rpl_endofnames(const Channel &chan){
    return "lmao";
}
const std::string bld_rpl_whoisidle(const User &user){
    return "lmao";
}

const std::string bld_rpl_topic_msg(const User &user, const Channel &chan){
    return "lmao";
}
const std::string bld_join_msg(const User &user, const Channel &chan){
    return ("Welcome to channel " + chan.get_name() + "\r\n");
}

const std::string bld_part_msg(const User &user, const Channel &chan, const std::string &message){
    return "lmao";
}
const std::string bld_nick_msg(const User &user, const std::string &nick){
    return "lmao";
}
const std::string bld_ping_msg(const User &user){
    return "lmao";
}
const std::string bld_pong_msg(const User &user){
    return "lmao";
}
const std::string bld_kick_msg(const User &oper, const User &target, const Channel &chan, const std::string reason){
    return "lmao";
}

const std::string bld_err_nicknameinuse(const User &user){
    return "lmao";
}
const std::string bld_err_nosuchnick(const std::string &name){
    return "lmao";
}
const std::string bld_err_chanoprivsneeded(const Channel &chan){
    return "lmao";
}
const std::string bld_err_nonicknamegiven(void){
    return "lmao";
}
const std::string bld_err_erroneusnickname(const std::string &nick){
    return "lmao";
}
const std::string bld_err_nosuchchannel(const std::string &chan){
    return "lmao";
}
const std::string bld_err_notonchannel(const Channel &chan){
    return "lmao";
}
const std::string bld_err_notonchannel(const std::string &chan){
    return "lmao";
}
const std::string bld_err_usernotinchannel(const std::string &user, const Channel &chan){
    return "lmao";
}
const std::string bld_err_unknowmode(const std::string &mode){
    return "lmao";
}
const std::string bld_err_usersdontmatch(void){
    return "lmao";
}
const std::string bld_err_umodeunknowflag(void){
    return "lmao";
}
const std::string bld_err_notexttosend(void){
    return "lmao";
}
const std::string bld_err_cannotsendtochan(const Channel &chan){
    return "lmao";
}
const std::string bld_err_needmoreparams(const std::string &cmd){
    return "lmao";
}
const std::string bld_err_needpass(void){
    return "lmao";
}

const std::string bld_bad_pass(void){
    return "lmao";
}