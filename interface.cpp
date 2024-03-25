#include <cstdio>
#include <iostream>

#include "User.h"
#include "UserManager.h"
#include "ServerCore.h"
#include "message_builder.h"


#define SUS "Welcome to Jugo's IRC Server"

#define BADPASS "Bad password"

#define NOPASS "NO PASSWORD WTF VRO"

const std::string bld_rpl_welcome(const User &user) {
	return "001 " + user.get_nickname() + " :Welcome to the Internet Relay Network\n" + SUS + "\r\n";
}

// const std::string bld_rpl_umodeis(const User &user) {
// 	return "221 " + user.get_prefix() + " +" + user.get_mode() + "\r\n";
// }

const std::string bld_rpl_topic(const Channel &chan) {
	return "332 " + chan.get_name() + " :" + chan.get_topic() + "\r\n";
}

const std::string bld_rpl_notopic(const Channel &chan) {
    return "331 " + chan.get_name() + " :No topic set\r\n";
}

const std::string bld_rpl_whoisuser(const User &user) {
    return "311 " + user.get_nickname() + " " + user.get_username() + " " + user.get_hostname() + " " + user.get_servername() + " * :" + user.get_realname() + "\r\n";
}

const std::string bld_rpl_whoisoperator(const User &user) {
    return "313 " + user.get_nickname() + " :is an IRC operator\r\n"; 
}

const std::string bld_rpl_endofwhois(const User &user) {
    return "318 " + user.get_nickname() + " :End of /WHOIS list\r\n";
}

const std::string bld_rpl_namreply(const Channel &chan) {
	return "353 = " + chan.get_name() + " :" + chan.get_username_list() + "\r\n";
}

const std::string bld_rpl_endofnames(const Channel &chan) {
	return "366 " + chan.get_name() + "\r\n";
}

// const std::string bld_rpl_whoisidle(const User &user) {
//     char tmp[10] = {0};
//     sprintf(tmp, "%ld", user.get_idle());
//     return "317 " + user.get_nickname() + " " + user.get_username() + " " + tmp + " :seconds idle\r\n";
// }
#include <iostream>
const std::string bld_join_msg(const User &user, const Channel &chan) {
    return  ":" + user.get_prefix() + " JOIN :" + chan.get_name()  + "\r\n";
}

const std::string bld_rpl_topic_msg(const User &user, const Channel &chan) {
    return ":" +user.get_prefix() + " TOPIC " + chan.get_name() + " :" + chan.get_topic() + "\r\n";
}
const std::string bld_privmsg_msg(const User &user, const Channel &chan, const std::string &message) {
    return ":" + user.get_prefix() + " PRIVMSG " + chan.get_name() + " :" + message + "\r\n";
}

const std::string bld_privmsg_msg(const User &user, const User &target, const std::string &message) {
    return ":" + user.get_prefix() + " PRIVMSG " + target.get_nickname() + " :" + message + "\r\n";
}

const std::string bld_part_msg(const User &user, const Channel &chan, const std::string &message) {
    return ":" + user.get_prefix() + " PART " + chan.get_name() + " :" + message + "\r\n";
}

const std::string bld_nick_msg(const User &user, const std::string &nick) {
    return ":" + user.get_nickname() + " NICK " + nick + "\r\n";
}

const std::string bld_ping_msg(const User &user) {
    return "PING :" + user.get_servername() + "\r\n";
}

const std::string bld_pong_msg(const User &user) {
	return ":" + user.get_servername() + " PONG\r\n";
}

const std::string bld_kick_msg(const User &oper, const User &target, const Channel &chan, const std::string reason) {
    if (reason != "")
    	return ":" + oper.get_nickname() + " KICK " + chan.get_name() + " " + target.get_nickname() + " :" + reason + "\r\n";
    return ":" + oper.get_nickname() + " KICK " + chan.get_name() + " " + target.get_nickname() + "\r\n";
}

const std::string bld_err_nicknameinuse(const User &user) {
    return "433 " + user.get_nickname() + " :" + user.get_nickname() + "\r\n";
}

const std::string bld_err_nosuchnick(const std::string &name) {
    return "401 " + name + " :" + name + "\r\n";
}

const std::string bld_err_chanoprivsneeded(const Channel &chan) {
    return "482 " + chan.get_name() + " :You're not channel operator\r\n";
}

const std::string bld_err_nonicknamegiven(void) {
    return "431 :No nickname given\r\n";
}

const std::string bld_err_erroneusnickname(const std::string &nick) {
    return "432 " + nick + " :Erroneus nickname\r\n";
}

const std::string bld_err_nonicknamegiven(void){
    return ("431 :No nickname given\r\n");
}

const std::string bld_err_nosuchchannel(const std::string &chan) {
    return "403 " + chan + " :No such channel\r\n";
}

const std::string bld_err_notonchannel(const Channel &chan) {
    return "442 " + chan.get_name() + " :You're not on that channel\r\n";
}

const std::string bld_err_notonchannel(const std::string &chan) {
    return "442 " + chan + " :You're not on that channel\r\n";
}

const std::string bld_err_usernotinchannel(const std::string &user, const Channel &chan) {
    return "441 " + user + " " + chan.get_name() + " :They aren't on that channel\r\n";
}

const std::string bld_err_unknowmode(const std::string &mode) {
    return "472 " + mode + " :is unknown mode char to me\r\n";
}

const std::string bld_err_usersdontmatch(void) {
    return "502 :Cant change mode for other users\r\n";
}

const std::string bld_err_umodeunknowflag(void) {
    return "501 :Unknown MODE flag\r\n";
}

const std::string bld_err_notexttosend(void) {
    return "412 :No text to send\r\n";
}

const std::string bld_err_cannotsendtochan(const Channel &chan) {
    return "404 " + chan.get_name() + " :No such channel\r\n";
}

const std::string bld_err_needmoreparams(const std::string &cmd) {
    return "461 " + cmd + " :Not enough parameters\r\n";
}

const std::string bld_err_needpass(void) {
    return "ERROR :" NOPASS "\r\n";
}

const std::string bld_bad_pass(void) {
    return "ERROR :" BADPASS "\r\n";
}

const std::string bld_err_alreadyregistred(void)
{
    return "462 :Unauthorized command (already registered)\r\n";
}

const std::string bld_err_unknowncmd(const std::string cmd)
{
    return "421 " + cmd + " :Unknown command\r\n";
}