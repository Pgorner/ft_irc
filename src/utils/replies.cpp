/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:12:52 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 18:21:50 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

namespace irc
{
    std::string cEM(const char* errorMessage)
    {
        std::string result(errorMessage); // Convert C-style string to std::string
        delete[] errorMessage; // Deallocate the memory
        return result;
    }
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

    const char* ERR_NOSUCHCHANNEL(const std::string& channel_name)
    {
        std::string outcome;
        std::cout << RED << "Given channel name is invalid!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 403 " + channel_name + " :No such channel\r\n";
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

    const char* ERR_PASSWDMISMATCH()
    {
        std::string outcome;
        std::cout << RED << "Password given for OPER command is incorrect!" << RESET << "\n";
        outcome += ":" + std::string(SERVERNAME) + " 464 :Password incorrect\r\n";
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
        outcome += ":" + std::string(SERVERNAME) + " 331 " + channel + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_TOPIC(const std::string& nick, const std::string& channel, const std::string& topic)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 332 " + nick+ " " + channel + " :" + topic + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }

    const char* RPL_INVITING(const std::string& yourNickname, const std::string& inviteeNickname, const std::string& channelName)
    {
        std::string outcome; 
        outcome += ":" + std::string(SERVERNAME) + " 341 " + yourNickname + " " + inviteeNickname + " " + channelName + "\r\n";
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
        outcome += ":" + std::string(SERVERNAME) + " 366 " + channel + " :" + channel + "\r\n";
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

    const char* RPL_UMODEIS(const std::string& user_mode_string)
    {
        std::string outcome;
        outcome += ":" + std::string(SERVERNAME) + " 221 :" + user_mode_string + "\r\n";
        char* cstr = new char[outcome.length() + 1];
        std::strcpy(cstr, outcome.c_str());
        return cstr;
    }
}