/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:12:52 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/22 16:11:03 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

namespace irc
{
    /***********************************************
    ERROR REPLIES
    ***********************************************/
    const char* ERR_NOSUCHNICK(const std::string& nickname, const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "User tried accessing a non-existent nickname or channel!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 401 " + nickname + " " + channel + " :No such nick/channel\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOSUCHSERVER(const std::string& server_name)
    {
        std::string outcome;
        std::cout << RED << "Server name provided does not exist!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 402 " + server_name + " :No such server\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOSUCHCHANNEL(const std::string& channel_name)
    {
        std::string outcome;
        std::cout << RED << "Given channel name is invalid!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 403 " + channel_name + " :No such channel\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_CANNOTSENDTOCHAN(const std::string& channel_name)
    {
        std::string outcome;
        std::cout << RED << "User tried to send a message to a channel they are not allowed to send!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 404 " + channel_name + " :Cannot send to channel\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_TOOMANYCHANNELS(const std::string& channel_name)
    {
        std::string outcome;
        std::cout << RED << "User has joined the maximum number of allowed channels!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 405 " + channel_name + " :You have joined too many channels\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_WASNOSUCHNICK(const std::string& nickname)
    {
        std::string outcome;
        std::cout << RED << "History information not found for the provided nickname!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 406 " + nickname + " :There was no such nickname\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_TOOMANYTARGETS(const std::string& target, const std::string& error_code, const std::string& abort_message)
    {
        std::string outcome;
        std::cout << RED << "Too many recipients or invalid target format for the command!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 407 " + target + " :" + error_code + " recipients. " + abort_message + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOSUCHSERVICE(const std::string& service_name)
    {
        std::string outcome;
        std::cout << RED << "The service being queried does not exist!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 408 " + service_name + " :No such service\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOORIGIN()
    {
        std::string outcome;
        std::cout << RED << "PING or PONG message missing the originator parameter!" << RESET << "\n";
        outcome += ": " + std::string(SERVERNAME) + " 409 :No origin specified\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NORECIPIENT()
    {
        std::string outcome;
        std::cout << RED << "A command is missing the recipient field!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 411 :No recipient given\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOTEXTTOSEND()
    {
        std::string outcome;
        std::cout << RED << "A command is missing the text to send!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 412 :No text to send\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOTOPLEVEL(const std::string& mask)
    {
        std::string outcome;
        std::cout << RED << "A mask used for a command doesn't specify a top-level domain!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 413 " + mask + " :No top-level domain specified\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_WILDTOPLEVEL(const std::string& mask)
    {
        std::string outcome;
        std::cout << RED << "A mask used for a command has a wildcard in the top-level domain!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 414 " + mask + " :Wildcard in top-level domain\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_BADMASK(const std::string& mask)
    {
        std::string outcome;
        std::cout << RED << "An invalid server/host mask is used!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 415 " + mask + " :Bad Server/host mask\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_UNKNOWNCOMMAND(const std::string& command)
    {
        std::string outcome;
        std::cout << RED << "A registered client attempted to execute an unknown command!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 421 " + command + " :Unknown command\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOMOTD()
    {
        std::string outcome;
        std::cout << RED << "The server's MOTD file could not be opened!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 422 :MOTD File is missing\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOADMININFO(const std::string& server)
    {
        std::string outcome;
        std::cout << RED << "Error finding appropriate information for the ADMIN message!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 423 " + server + " :No administrative info available\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_FILEERROR(const std::string& file_op, const std::string& file)
    {
        std::string outcome;
        std::cout << RED << "A generic error occurred during a file operation!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 424 :File error doing " + file_op + " on " + file + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NONICKNAMEGIVEN()
    {
        std::string outcome;
        std::cout << RED << "A nickname parameter expected for a command is not found!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 431 :No nickname given\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_ERRONEUSNICKNAME(const std::string& nick)
    {
        std::string outcome;
        std::cout << RED << "The provided nickname contains characters not falling in the defined set!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 432 " + nick + " :Erroneous nickname\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NICKNAMEINUSE(const std::string& nick)
    {
        std::string outcome;
        std::cout << RED << "A NICK message is processed that results in an attempt to change to an existing nickname!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 433 " + nick + " :Nickname is already in use\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NICKCOLLISION(const std::string& nick, const std::string& user, const std::string& host)
    {
        std::string outcome;
        std::cout << RED << "Two clients are trying to use the same nickname!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 436 " + nick + " " + user + " " + host + " :Nickname collision KILL\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_UNAVAILRESOURCE(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An attempt to join a channel that requires an invitation without an invite!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 437 " + channel + " :Cannot change nickname while banned on channel or channel requires an invitation\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_USERNOTINCHANNEL(const std::string& nick, const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An operator command is used with a nickname that is not on the specified channel!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 441 " + nick + " " + channel + " :They aren't on that channel\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOTONCHANNEL(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "A command expected the client to be on a channel!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 442 " + channel + " :You're not on that channel\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_USERONCHANNEL(const std::string& nick, const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An operator command is used with a nickname that is already on the specified channel!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 443 " + nick + " " + channel + " :is already on channel\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOLOGIN(const std::string& user)
    {
        std::string outcome;
        std::cout << RED << "An OPER command was sent with an invalid user login!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 444 " + user + " :User not logged in\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_SUMMONDISABLED()
    {
        std::string outcome;
        std::cout << RED << "The server's SUMMON command is disabled!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 445 :SUMMON has been disabled\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_USERSDISABLED()
    {
        std::string outcome;
        std::cout << RED << "The server's USERS command is disabled!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 446 :USERS has been disabled\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOTREGISTERED()
    {
        std::string outcome;
        std::cout << RED << "The client is trying to perform a normal command before registering!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 451 :You have not registered\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NEEDMOREPARAMS(const std::string& command)
    {
        std::string outcome;
        std::cout << RED << "More Parameters needed to execute command: " << command << "!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 461 " + command + " :Not enough parameters\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_ALREADYREGISTRED()
    {
        std::string outcome;
        std::cout << RED << "The client is already registered and cannot register twice!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 462 :You may not reregister\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOPERMFORHOST()
    {
        std::string outcome;
        std::cout << RED << "The client's host is banned from this server!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 463 :Your host isn't among the privileged\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_PASSWDMISMATCH()
    {
        std::string outcome;
        std::cout << RED << "Password given for OPER command is incorrect!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 464 :Password incorrect\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_YOUREBANNEDCREEP()
    {
        std::string outcome;
        std::cout << RED << "The client is banned from the server!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 465 :You are banned from this server\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_KEYSET(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An attempt to join a channel that requires a key without a correct key!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 467 " + channel + " :Channel key already set\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_CHANNELISFULL(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An attempt to join a channel that is already full!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 471 " + channel + " :Cannot join channel (+l)\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_UNKNOWNMODE(const std::string& mode_char)
    {
        std::string outcome;
        std::cout << RED << "An attempt to add or remove a mode that is not known!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 472 " + mode_char + " :is unknown mode char to me\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_INVITEONLYCHAN(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An attempt to join an invite-only channel without an invitation!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 473 " + channel + " :Cannot join channel (+i)\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_BANNEDFROMCHAN(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An attempt to join a channel the user is banned from!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 474 " + channel + " :Cannot join channel (+b)\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_BADCHANNELKEY(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An attempt to join a keyed channel with the wrong key!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 475 " + channel + " :Cannot join channel (+k)\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOPRIVILEGES()
    {
        std::string outcome;
        std::cout << RED << "The client's privilege level is insufficient to perform the command!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 481 :Permission Denied- You're not an IRC operator\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_CHANOPRIVSNEEDED(const std::string& channel)
    {
        std::string outcome;
        std::cout << RED << "An operator command is used without having the correct privileges!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 482 " + channel + " :You're not channel operator\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_CANTKILLSERVER()
    {
        std::string outcome;
        std::cout << RED << "The client is trying to KILL a server!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 483 :You cant kill a server!\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_NOOPERHOST()
    {
        std::string outcome;
        std::cout << RED << "The client's host is not among the privileged for OPER!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 491 :No O-lines for your host\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_UMODEUNKNOWNFLAG()
    {
        std::string outcome;
        std::cout << RED << "An unknown mode flag is given for the user!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 501 :Unknown MODE flag\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* ERR_USERSDONTMATCH()
    {
        std::string outcome;
        std::cout << RED << "A user cannot change modes for other users!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 502 :Cannot change mode for other users\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }
    /***********************************************
    RPL REPLIES
    ***********************************************/
    const char* RPL_WELCOME(const std::string& nick, const std::string& user, const std::string& host)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 001 " + nick + " !" + user + " @" + host +" Welcome to the Internet Relay Network\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_YOURHOST(const std::string& version)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 002 Your host is " + std::string(SERVERNAME) + ", running version " + version + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_CREATED(const std::string& date)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 003 This server was created " + date + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_MYINFO(const std::string& version, const std::string& available_user_modes, const std::string& available_channel_modes)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 004 " + std::string(SERVERNAME) + " " + version + " " + available_user_modes + " " + available_channel_modes + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_BOUNCE(const std::string& server_name, int port_number)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 005 Try server " + server_name + ", port " + std::to_string(port_number) + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_USERHOST(const std::string& reply, const std::vector<std::string>& replies)
    {
        std::string outcome = ":";
        std::string userhostrpl;
        for (std::vector<std::string>::const_iterator it = replies.begin(); it != replies.end(); ++it)
        {
            userhostrpl += " " + *it;
        }
        outcome += std::string(SERVERNAME) + reply + " 302 :" + userhostrpl + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ISON(const std::vector<std::string>& nicknames)
    {
        std::string outcome;
        std::string nick_list;
        for (std::vector<std::string>::const_iterator it = nicknames.begin(); it != nicknames.end(); ++it)
        {
            nick_list += " " + *it;
        }
        outcome += ":" + std::string(SERVERNAME) + " 303 " + nick_list + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }


    const char* RPL_AWAY(const std::string& nick, const std::string& away_message)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 301 " + nick + " :" + away_message + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_UNAWAY()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 305 :You are no longer marked as being away\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_NOWAWAY()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 306 :You have been marked as being away\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_WHOISUSER(const std::string& nick, const std::string& user, const std::string& host, const std::string& real_name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 311 " + nick + " " + user + " " + host + " * :" + real_name + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_WHOISSERVER(const std::string& nick, const std::string& server, const std::string& server_info)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 312 " + nick + " " + server + " :" + server_info + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_WHOISOPERATOR(const std::string& nick)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 313 " + nick + " :is an IRC operator\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_WHOISIDLE(const std::string& nick, int seconds_idle)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 317 " + nick + " " + std::to_string(seconds_idle) + " :seconds idle\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFWHOIS(const std::string& nick)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 318 " + nick + " :End of WHOIS list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_WHOISCHANNELS(const std::string& nick, const std::vector<std::string>& channels)
    {
        std::string outcome = ":";
        std::string channel_list;
        for (std::vector<std::string>::const_iterator it = channels.begin(); it != channels.end(); ++it)
        {
            channel_list += " " + *it;
        }
        outcome += std::string(SERVERNAME) + " 319 " + nick + " :" + channel_list + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }


    const char* RPL_WHOWASUSER(const std::string& nick, const std::string& user, const std::string& host, const std::string& real_name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 314 " + nick + " " + user + " " + host + " * :" + real_name + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFWHOWAS(const std::string& nick)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 369 " + nick + " :End of WHOWAS\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LISTSTART()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 321 Obsolete. Not used.\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LIST(const std::string& channel, int num_visible, const std::string& topic)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 322 " + channel + " " + std::to_string(num_visible) + " :" + topic + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LISTEND()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 323 :End of LIST\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_UNIQOPIS(const std::string& channel, const std::string& nickname)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 325 " + channel + " " + nickname + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_CHANNELMODEIS(const std::string& channel, const std::string& mode, const std::string& mode_params)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 324 " + channel + " " + mode + " " + mode_params + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_NOTOPIC(const std::string& channel)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 331 " + channel + " :No topic is set\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TOPIC(const std::string& channel, const std::string& topic)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 332 " + channel + " :" + topic + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_INVITING(const std::string& channel, const std::string& nick)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 341 " + channel + " " + nick + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_SUMMONING(const std::string& user)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 342 " + user + " :Summoning user to IRC\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_INVITELIST(const std::string& channel, const std::string& invitemask)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 346 " + channel + " " + invitemask + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFINVITELIST(const std::string& channel)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 347 " + channel + " :End of channel invite list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_EXCEPTLIST(const std::string& channel, const std::string& exceptionmask)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 348 " + channel + " " + exceptionmask + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFEXCEPTLIST(const std::string& channel)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 349 " + channel + " :End of channel exception list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_VERSION(const std::string& version, const std::string& server, const std::string& comments)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 351 " + version + " " + server + " :" + comments + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_WHOREPLY(const std::string& channel, const std::string& user, const std::string& host, const std::string& server, const std::string& nick, const std::string& hopcount, const std::string& real_name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 352 " + channel + " " + user + " " + host + " " + server + " " + nick + " H" + hopcount + " : " + real_name + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFWHO(const std::string& name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 315 " + name + " :End of WHO list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_NAMREPLY(const std::string& channel, const std::string& nick_list)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 353 = " + channel + " :" + nick_list + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFNAMES(const std::string& channel)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 366 " + channel + " :End of NAMES list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LINKS(const std::string& mask, const std::string& server, const std::string& hopcount, const std::string& server_info)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 364 " + mask + " " + server + " :" + hopcount + " " + server_info + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFLINKS(const std::string& mask)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 365 " + mask + " :End of LINKS list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_BANLIST(const std::string& channel, const std::string& banmask)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 367 " + channel + " " + banmask + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFBANLIST(const std::string& channel)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 368 " + channel + " :End of channel ban list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_INFO(const std::string& info)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 371 :" + info + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFINFO()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 374 :End of INFO list\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_MOTDSTART(const std::string& server)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 375 :- " + server + " Message of the day - \r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_MOTD(const std::string& text)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 372 :- " + text + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFMOTD()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 376 :End of MOTD command\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_YOUREOPER()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 381 :You are now an IRC operator\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_REHASHING(const std::string& config_file)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 382 " + config_file + " :Rehashing\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_YOURESERVICE(const std::string& servicename)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 383 You are service " + servicename + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TIME(const std::string& server, const std::string& time)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 391 " + server + " :" + time + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_USERSSTART()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 392 :UserID   Terminal  Host\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_USERS(const std::string& username, const std::string& ttyline, const std::string& hostname)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 393 :" + username + " " + ttyline + " " + hostname + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFUSERS()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 394 :End of users\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_NOUSERS()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 395 :Nobody logged in\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACELINK(const std::string& version_debug, const std::string& destination, const std::string& next_server, const std::string& protocol_version, const std::string& link_uptime, const std::string& backstream_sendq, const std::string& upstream_sendq)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 200 Link " + version_debug + " " + destination + " " + next_server + " V" + protocol_version + " " + link_uptime + " " + backstream_sendq + " " + upstream_sendq + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACECONNECTING(const std::string& irc_class, const std::string& server)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 201 Try. " + irc_class + " " + server + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACEHANDSHAKE(const std::string& irc_class, const std::string& server)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 202 H.S. " + irc_class + " " + server + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACEUNKNOWN(const std::string& irc_class, const std::string& client_ip)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 203 ???? " + irc_class + " [" + client_ip + "]\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACEOPERATOR(const std::string& irc_class, const std::string& nick)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 204 Oper " + irc_class + " " + nick + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACEUSER(const std::string& irc_class, const std::string& nick)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 205 User " + irc_class + " " + nick + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACESERVER(const std::string& irc_class, const std::string& intS, const std::string& intC, const std::string& server, const std::string& user_host, const std::string& protocol_version)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 206 Serv " + irc_class + " " + intS + " " + intC + " " + server + " " + user_host + " V" + protocol_version + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACESERVICE(const std::string& irc_class, const std::string& name, const std::string& type, const std::string& active_type)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 207 Service " + irc_class + " " + name + " " + type + " " + active_type + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACENEWTYPE(const std::string& newtype, const std::string& client_name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 208 " + newtype + " 0 " + client_name + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACECLASS(const std::string& irc_class, const std::string& count)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 209 Class " + irc_class + " " + count + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACERECONNECT()
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 210 Unused.\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACELOG(const std::string& logfile, const std::string& debug_level)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 261 File " + logfile + " " + debug_level + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRACEEND(const std::string& server_name, const std::string& version_debug)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 262 " + server_name + " " + version_debug + " :End of TRACE\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_STATSLINKINFO(const std::string& linkname, const std::string& sendq, const std::string& sent_messages, const std::string& sent_kbytes, const std::string& received_messages, const std::string& received_kbytes, const std::string& time_open)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 211 " + linkname + " " + sendq + " " + sent_messages + " " + sent_kbytes + " " + received_messages + " " + received_kbytes + " " + time_open + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_STATSCOMMANDS(const std::string& command, const std::string& count, const std::string& byte_count, const std::string& remote_count)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 212 " + command + " " + count + " " + byte_count + " " + remote_count + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ENDOFSTATS(const std::string& stats_letter)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 219 " + stats_letter + " :End of STATS report\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_STATSUPTIME(int days, int hours, int minutes, int seconds)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 242 :Server Up " + std::to_string(days) + " days " + std::to_string(hours) + outcome += ":" + std::to_string(minutes) + outcome += ":" + std::to_string(seconds) + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_STATSOLINE(const std::string& hostmask, const std::string& name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 243 O " + hostmask + " * " + name + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_UMODEIS(const std::string& user_mode_string)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 221 +" + user_mode_string + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_SERVLIST(const std::string& name, const std::string& server, const std::string& mask, const std::string& type, const std::string& hopcount, const std::string& info)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 234 " + name + " " + server + " " + mask + " " + type + " " + hopcount + " " + info + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_SERVLISTEND(const std::string& mask, const std::string& type)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 235 " + mask + " " + type + " :End of service listing\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LUSERCLIENT(const std::string& num_users, const std::string& num_services, const std::string& num_servers)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 251 :There are " + num_users + " users and " + num_services + " services on " + num_servers + " servers\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LUSEROP(const std::string& num_operators)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 252 " + num_operators + " :operator(s) online\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LUSERUNKNOWN(const std::string& num_unknown)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 253 " + num_unknown + " :unknown connection(s)\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LUSERCHANNELS(const std::string& num_channels)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 254 " + num_channels + " :channels formed\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_LUSERME(const std::string& num_clients, const std::string& num_servers)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 255 :I have " + num_clients + " clients and " + num_servers + " servers\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ADMINME(const std::string& server_name)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 256 " + server_name + " :Administrative info\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ADMINLOC1(const std::string& admin_info)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 257 :Location " + admin_info + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ADMINLOC2(const std::string& admin_info)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 258 :Location " + admin_info + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_ADMINEMAIL(const std::string& admin_email)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 259 :Email " + admin_email + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TRYAGAIN(const std::string& command)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 263 " + command + " :Please wait a while and try again\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }
}