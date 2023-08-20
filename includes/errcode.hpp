/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:04:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/04 18:07:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERROR_CODES_HPP
#define IRC_ERROR_CODES_HPP

#include "irc.hpp"
#include "typography.hpp"
#include "server.hpp"
#include <iostream>
#include <sstream>

namespace irc
{
    /***********************************************
    ERROR REPLIES
    ***********************************************/
    std::string ERR_NOSUCHNICK(const std::string& nickname, const std::string& channel)
    {
        std::cout << RED << "User tried accessing a non-existent nickname or channel!" << RESET << "\n";
        return ":" + SERVERNAME + " 401 " + nickname + " " + channel + " :No such nick/channel\r\n";
    }

    std::string ERR_NOSUCHSERVER(const std::string& server_name)
    {
        std::cout << RED << "Server name provided does not exist!" << RESET << "\n";
        return ":" + SERVERNAME + " 402 " + server_name + " :No such server\r\n";
    }

    std::string ERR_NOSUCHCHANNEL(const std::string& channel_name)
    {
        std::cout << RED << "Given channel name is invalid!" << RESET << "\n";
        return ":" + SERVERNAME + " 403 " + channel_name + " :No such channel\r\n";
    }

    std::string ERR_CANNOTSENDTOCHAN(const std::string& channel_name)
    {
        std::cout << RED << "User tried to send a message to a channel they are not allowed to send!" << RESET << "\n";
        return ":" + SERVERNAME + " 404 " + channel_name + " :Cannot send to channel\r\n";
    }

    std::string ERR_TOOMANYCHANNELS(const std::string& channel_name)
    {
        std::cout << RED << "User has joined the maximum number of allowed channels!" << RESET << "\n";
        return ":" + SERVERNAME + " 405 " + channel_name + " :You have joined too many channels\r\n";
    }

    std::string ERR_WASNOSUCHNICK(const std::string& nickname)
    {
        std::cout << RED << "History information not found for the provided nickname!" << RESET << "\n";
        return ":" + SERVERNAME + " 406 " + nickname + " :There was no such nickname\r\n";
    }

    std::string ERR_TOOMANYTARGETS(const std::string& target, const std::string& error_code, const std::string& abort_message)
    {
        std::cout << RED << "Too many recipients or invalid target format for the command!" << RESET << "\n";
        return ":" + SERVERNAME + " 407 " + target + " :" + error_code + " recipients. " + abort_message + "\r\n";
    }

    std::string ERR_NOSUCHSERVICE(const std::string& service_name)
    {
        std::cout << RED << "The service being queried does not exist!" << RESET << "\n";
        return ":" + SERVERNAME + " 408 " + service_name + " :No such service\r\n";
    }

    std::string ERR_NOORIGIN()
    {
        std::cout << RED << "PING or PONG message missing the originator parameter!" << RESET << "\n";
        return ": " + SERVERNAME + " 409 :No origin specified\r\n";
    }

    std::string ERR_NORECIPIENT()
    {
        std::cout << RED << "A command is missing the recipient field!" << RESET << "\n";
        return ":" + SERVERNAME + " 411 :No recipient given\r\n";
    }

    std::string ERR_NOTEXTTOSEND()
    {
        std::cout << RED << "A command is missing the text to send!" << RESET << "\n";
        return ":" + SERVERNAME + " 412 :No text to send\r\n";
    }

    std::string ERR_NOTOPLEVEL(const std::string& mask)
    {
        std::cout << RED << "A mask used for a command doesn't specify a top-level domain!" << RESET << "\n";
        return ":" + SERVERNAME + " 413 " + mask + " :No top-level domain specified\r\n";
    }

    std::string ERR_WILDTOPLEVEL(const std::string& mask)
    {
        std::cout << RED << "A mask used for a command has a wildcard in the top-level domain!" << RESET << "\n";
        return ":" + SERVERNAME + " 414 " + mask + " :Wildcard in top-level domain\r\n";
    }

    std::string ERR_BADMASK(const std::string& mask)
    {
        std::cout << RED << "An invalid server/host mask is used!" << RESET << "\n";
        return ":" + SERVERNAME + " 415 " + mask + " :Bad Server/host mask\r\n";
    }

    std::string ERR_UNKNOWNCOMMAND(const std::string& command)
    {
        std::cout << RED << "A registered client attempted to execute an unknown command!" << RESET << "\n";
        return ":" + SERVERNAME + " 421 " + command + " :Unknown command\r\n";
    }

    std::string ERR_NOMOTD()
    {
        std::cout << RED << "The server's MOTD file could not be opened!" << RESET << "\n";
        return ":" + SERVERNAME + " 422 :MOTD File is missing\r\n";
    }

    std::string ERR_NOADMININFO(const std::string& server)
    {
        std::cout << RED << "Error finding appropriate information for the ADMIN message!" << RESET << "\n";
        return ":" + SERVERNAME + " 423 " + server + " :No administrative info available\r\n";
    }

    std::string ERR_FILEERROR(const std::string& file_op, const std::string& file)
    {
        std::cout << RED << "A generic error occurred during a file operation!" << RESET << "\n";
        return ":" + SERVERNAME + " 424 :File error doing " + file_op + " on " + file + "\r\n";
    }

    std::string ERR_NONICKNAMEGIVEN()
    {
        std::cout << RED << "A nickname parameter expected for a command is not found!" << RESET << "\n";
        return ":" + SERVERNAME + " 431 :No nickname given\r\n";
    }

    std::string ERR_ERRONEUSNICKNAME(const std::string& nick)
    {
        std::cout << RED << "The provided nickname contains characters not falling in the defined set!" << RESET << "\n";
        return ":" + SERVERNAME + " 432 " + nick + " :Erroneous nickname\r\n";
    }

    std::string ERR_NICKNAMEINUSE(const std::string& nick)
    {
        std::cout << RED << "A NICK message is processed that results in an attempt to change to an existing nickname!" << RESET << "\n";
        return ":" + SERVERNAME + " 433 " + nick + " :Nickname is already in use\r\n";
    }

    std::string ERR_NICKCOLLISION(const std::string& nick, const std::string& user, const std::string& host)
    {
        std::cout << RED << "Two clients are trying to use the same nickname!" << RESET << "\n";
        return ":" + SERVERNAME + " 436 " + nick + " " + user + " " + host + " :Nickname collision KILL\r\n";
    }

    std::string ERR_UNAVAILRESOURCE(const std::string& channel, const std::string& action)
    {
        std::cout << RED << "An attempt to join a channel that requires an invitation without an invite!" << RESET << "\n";
        return ":" + SERVERNAME + " 437 " + channel + " :Cannot change nickname while banned on channel or channel requires an invitation\r\n";
    }

    std::string ERR_USERNOTINCHANNEL(const std::string& nick, const std::string& channel)
    {
        std::cout << RED << "An operator command is used with a nickname that is not on the specified channel!" << RESET << "\n";
        return ":" + SERVERNAME + " 441 " + nick + " " + channel + " :They aren't on that channel\r\n";
    }

    std::string ERR_NOTONCHANNEL(const std::string& channel)
    {
        std::cout << RED << "A command expected the client to be on a channel!" << RESET << "\n";
        return ":" + SERVERNAME + " 442 " + channel + " :You're not on that channel\r\n";
    }

    std::string ERR_USERONCHANNEL(const std::string& nick, const std::string& channel)
    {
        std::cout << RED << "An operator command is used with a nickname that is already on the specified channel!" << RESET << "\n";
        return ":" + SERVERNAME + " 443 " + nick + " " + channel + " :is already on channel\r\n";
    }

    std::string ERR_NOLOGIN(const std::string& user)
    {
        std::cout << RED << "An OPER command was sent with an invalid user login!" << RESET << "\n";
        return ":" + SERVERNAME + " 444 " + user + " :User not logged in\r\n";
    }

    std::string ERR_SUMMONDISABLED()
    {
        std::cout << RED << "The server's SUMMON command is disabled!" << RESET << "\n";
        return ":" + SERVERNAME + " 445 :SUMMON has been disabled\r\n";
    }

    std::string ERR_USERSDISABLED()
    {
        std::cout << RED << "The server's USERS command is disabled!" << RESET << "\n";
        return ":" + SERVERNAME + " 446 :USERS has been disabled\r\n";
    }

    std::string ERR_NOTREGISTERED()
    {
        std::cout << RED << "The client is trying to perform a normal command before registering!" << RESET << "\n";
        return ":" + SERVERNAME + " 451 :You have not registered\r\n";
    }

    std::string ERR_NEEDMOREPARAMS(const std::string& command)
    {
        std::cout << RED << "More Parameters needed to execute command: " << command << "!" << RESET << "\n";
        return ":" + SERVERNAME + " 461 " + command + " :Not enough parameters\r\n";
    }

    std::string ERR_ALREADYREGISTRED()
    {
        std::cout << RED << "The client is already registered and cannot register twice!" << RESET << "\n";
        return ":" + SERVERNAME + " 462 :You may not reregister\r\n";
    }

    std::string ERR_NOPERMFORHOST()
    {
        std::cout << RED << "The client's host is banned from this server!" << RESET << "\n";
        return ":" + SERVERNAME + " 463 :Your host isn't among the privileged\r\n";
    }

    std::string ERR_PASSWDMISMATCH()
    {
        std::cout << RED << "Password given for OPER command is incorrect!" << RESET << "\n";
        return ":" + SERVERNAME + " 464 :Password incorrect\r\n";
    }

    std::string ERR_YOUREBANNEDCREEP()
    {
        std::cout << RED << "The client is banned from the server!" << RESET << "\n";
        return ":" + SERVERNAME + " 465 :You are banned from this server\r\n";
    }

    std::string ERR_KEYSET(const std::string& channel)
    {
        std::cout << RED << "An attempt to join a channel that requires a key without a correct key!" << RESET << "\n";
        return ":" + SERVERNAME + " 467 " + channel + " :Channel key already set\r\n";
    }

    std::string ERR_CHANNELISFULL(const std::string& channel)
    {
        std::cout << RED << "An attempt to join a channel that is already full!" << RESET << "\n";
        return ":" + SERVERNAME + " 471 " + channel + " :Cannot join channel (+l)\r\n";
    }

    std::string ERR_UNKNOWNMODE(const std::string& mode_char)
    {
        std::cout << RED << "An attempt to add or remove a mode that is not known!" << RESET << "\n";
        return ":" + SERVERNAME + " 472 " + mode_char + " :is unknown mode char to me\r\n";
    }

    std::string ERR_INVITEONLYCHAN(const std::string& channel)
    {
        std::cout << RED << "An attempt to join an invite-only channel without an invitation!" << RESET << "\n";
        return ":" + SERVERNAME + " 473 " + channel + " :Cannot join channel (+i)\r\n";
    }

    std::string ERR_BANNEDFROMCHAN(const std::string& channel)
    {
        std::cout << RED << "An attempt to join a channel the user is banned from!" << RESET << "\n";
        return ":" + SERVERNAME + " 474 " + channel + " :Cannot join channel (+b)\r\n";
    }

    std::string ERR_BADCHANNELKEY(const std::string& channel)
    {
        std::cout << RED << "An attempt to join a keyed channel with the wrong key!" << RESET << "\n";
        return ":" + SERVERNAME + " 475 " + channel + " :Cannot join channel (+k)\r\n";
    }

    std::string ERR_NOPRIVILEGES()
    {
        std::cout << RED << "The client's privilege level is insufficient to perform the command!" << RESET << "\n";
        return ":" + SERVERNAME + " 481 :Permission Denied- You're not an IRC operator\r\n";
    }

    std::string ERR_CHANOPRIVSNEEDED(const std::string& channel)
    {
        std::cout << RED << "An operator command is used without having the correct privileges!" << RESET << "\n";
        return ":" + SERVERNAME + " 482 " + channel + " :You're not channel operator\r\n";
    }

    std::string ERR_CANTKILLSERVER()
    {
        std::cout << RED << "The client is trying to KILL a server!" << RESET << "\n";
        return ":" + SERVERNAME + " 483 :You cant kill a server!\r\n";
    }

    std::string ERR_NOOPERHOST()
    {
        std::cout << RED << "The client's host is not among the privileged for OPER!" << RESET << "\n";
        return ":" + SERVERNAME + " 491 :No O-lines for your host\r\n";
    }

    std::string ERR_UMODEUNKNOWNFLAG()
    {
        std::cout << RED << "An unknown mode flag is given for the user!" << RESET << "\n";
        return ":" + SERVERNAME + " 501 :Unknown MODE flag\r\n";
    }

    std::string ERR_USERSDONTMATCH()
    {
        std::cout << RED << "A user cannot change modes for other users!" << RESET << "\n";
        return ":" + SERVERNAME + " 502 :Cannot change mode for other users\r\n";
    }

    // Add more error replies here if needed...

} // namespace irc



#define PIGEON1 "\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&@@@@@@@@@@@@\n\
#%###%#####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&%%&%&&&&&&&&&&&&&&&@@&@@@\n\
#############################%%%%%%%%%%%%%%%%%%%%%%%%%&%&&&&&&&&&&&&&&&&&&&@@@@@\n\
&&&&%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%&&&&&&&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@\n\
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@@@@@@\n\
&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&@@@@@\n\
%%&&&%%%&%##&&&&&&&&&&&&&&&&&&&&&%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@\n\
&%&%&&&&&&(%////*&&&&&&&&&%#/%%%%%%%%%%%%%%%#(&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\
%%%%%&&&&&%#%/////(///*/(/%%%%%%/*****%%%%%/%%%%%%(&&&&&&%&&&&&&&&&&&&&&&&&&&&&&\n\
%%&%&%&%&%%&&///////////#%%%***/%****%%%%%%%%%%%%%%%%(%%%%&%%&&&&&%%&&&&&&&&&&&&\n\
%%%%%%%%%%%&%%%&&%**////%%%/***%%***,%%%%%%%%%%%%%%%%%%#%%%%%%%%&%%%%%%&%&&&&&&&\n\
%%%%%%%%%&%%%%%%&%#%&///(%%%/**%%****%%%%%%%%%%%%%%%%%%(//#%%%%%%%%%%%%%&&%%%%&&\n\
%%%%%%%%%%%%%%%#%%%%%%&%%*%%%/*%%%**,%%%%%%%%%%%%%%%%%%//////(/(/%%%%%&%&%&&%&&&\n\
%%%%%%%%%%%%#%%%%%%%%%%%%%%%/#%%#%%**%%%%%%%%%%%%%%%%#//////////(//%%%%%%%%%&%%%\n\
%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%#(#(,,%%%%%%%%%%###(//////////,,///%%%%%%%%%%%%%\n\
%%%%%%#%%%%%%%%%%%%%%%%%%%%%%(//////*##/,******//////////////////&%%%%%%%%%%%%%%\n\
%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%(/*(*****//////*,,********(####(&&(%%%%%%%%%%%%%\n\
##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%/**/*//////(%%%%%%%%%%%%%%%%%(%%%%%*%%%%%%%%\n\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\
%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"

#define PIGEON2 "\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&@@@@@@@@@@@@\n\
#####%#####%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&%&&&&&&&&&&&&&&&&&&&&@@@@@@\n\
##############################%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&@@@@@\n\
&&&&%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%&&&&&&&&&&&&&&&&&&@&&@@@@@@@@@@@@@@@@@\n\
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@@@@@\n\
&&&&&&&&%&&&&&&&&&&&&&&&&&&&&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@@\n\
%%&&&&&%&&##&&&&&&&&&&&&&&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@\n\
&%&%&&&&&%(%///(*&&&&&&&&&&%/%%%%%%%%%%%%%%%%(%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\
%%%%%&&&&&%(%////////**/(/%%%%%%(*****%%%%%(#%%%%%%(&&&&&%&&&&&&&&&&&&&&&&&&&&&&\n\
%%&%%%&&&&%&&///////////#%%%****%****%%%%%%%%%%%%%%%%%%%%%&%%&&&&&%%&&&&&&&&&&&&\n\
%%%%%&%%%%%&%&&&&%**////%%%/***%%****%%%%%%%%%%%%%%%%%%%//#%%%%%&%%%&%%&&%&&&&&&\n\
%%%%%%%%%&%%%%%%%%#%&(//(%%%/**%%****%%%%%%%%%%%%%%%%%%%////////((%%%%%%&%%%%%&&\n\
%%%%%%%%%%%%%%%#%%%%%%%%%*%%%(*%%%**,%%%%%%%%%%%%%%%%%%(////////(//%%&&%&%&&%&&&\n\
%%%%%%%%%%%%#%%%%%%%%%%%%%%%/#%%(%%**%%%%%%%%%%%%%%%%#////////.,/((%%%%%%%%%%%%%\n\
%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%#/##,,%%%%%%%%%%###(/////////////(%%%%%%%%%%%%%%\n\
%%%%%%#%%%%%%%%%%%%%%%%%%%%%%(//////*##/,*******///////**,*(%%%%##&%%%%%%%%%%%%%\n\
%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%(//(*/***///////#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\
%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%/**/**/////(%%%%%%%%%%%%%%%%%(%%%%%*%%%%%%%%\n\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%###%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
#endif // IRC_ERROR_CODES_HPP
