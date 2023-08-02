/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:04:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/02 19:38:35 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERROR_CODES_HPP
#define IRC_ERROR_CODES_HPP

// Used to indicate the nickname parameter supplied to a command is currently unused.
#define ERR_NOSUCHNICK 401
#define ERR_NOSUCHNICK_MSG "<nickname> :No such nick/channel"

// Used to indicate the server name given currently does not exist.
#define ERR_NOSUCHSERVER 402
#define ERR_NOSUCHSERVER_MSG "<server name> :No such server"

// Used to indicate the given channel name is invalid.
#define ERR_NOSUCHCHANNEL 403
#define ERR_NOSUCHCHANNEL_MSG "<channel name> :No such channel"

// Sent to a user who is either (a) not on a channel which is mode +n or (b) not a chanop (or mode +v) on a channel which has mode +m set or where the user is banned and is trying to send a PRIVMSG message to that channel.
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_CANNOTSENDTOCHAN_MSG "<channel name> :Cannot send to channel"

// Sent to a user when they have joined the maximum number of allowed channels and they try to join another channel.
#define ERR_TOOMANYCHANNELS 405
#define ERR_TOOMANYCHANNELS_MSG "<channel name> :You have joined too many channels"

// Returned by WHOWAS to indicate there is no history information for that nickname.
#define ERR_WASNOSUCHNICK 406
#define ERR_WASNOSUCHNICK_MSG "<nickname> :There was no such nickname"

// Returned to a client which is attempting to send a PRIVMSG/NOTICE using the user@host destination format and for a user@host which has several occurrences.
// Returned to a client which trying to send a PRIVMSG/NOTICE to too many recipients.
// Returned to a client which is attempting to JOIN a safe channel using the shortname when there are more than one such channel.
#define ERR_TOOMANYTARGETS 407
#define ERR_TOOMANYTARGETS_MSG "<target> :<error code> recipients. <abort message>"

// Returned to a client which is attempting to send a SQUERY to a service which does not exist.
#define ERR_NOSUCHSERVICE 408
#define ERR_NOSUCHSERVICE_MSG "<service name> :No such service"

// PING or PONG message missing the originator parameter.
#define ERR_NOORIGIN 409
#define ERR_NOORIGIN_MSG ":No origin specified"

// Sent when a command is missing the recipient field (e.g., no target nickname or channel provided).
#define ERR_NORECIPIENT 411
#define ERR_NORECIPIENT_MSG ":No recipient given"





// Sent when a command is missing the text to send (e.g., no message content provided).
#define ERR_NOTEXTTOSEND 412
#define ERR_NOTEXTTOSEND_MSG ":No text to send"

// Sent when a mask used for a command doesn't specify a top-level domain.
#define ERR_NOTOPLEVEL 413
#define ERR_NOTOPLEVEL_MSG "<mask> :No top-level domain specified"

// Sent when a mask used for a command has a wildcard in the top-level domain.
#define ERR_WILDTOPLEVEL 414
#define ERR_WILDTOPLEVEL_MSG "<mask> :Wildcard in top-level domain"

// Sent when an invalid server/host mask is used.
#define ERR_BADMASK 415
#define ERR_BADMASK_MSG "<mask> :Bad Server/host mask"

// Returned to a registered client to indicate that the command sent is unknown by the server.
#define ERR_UNKNOWNCOMMAND 421
#define ERR_UNKNOWNCOMMAND_MSG "<command> :Unknown command"

// Sent when the server's MOTD file could not be opened by the server.
#define ERR_NOMOTD 422
#define ERR_NOMOTD_MSG ":MOTD File is missing"

// Returned by a server in response to an ADMIN message when there is an error in finding the appropriate information.
#define ERR_NOADMININFO 423
#define ERR_NOADMININFO_MSG "<server> :No administrative info available"

// Generic error message used to report a failed file operation during the processing of a message.
#define ERR_FILEERROR 424
#define ERR_FILEERROR_MSG ":File error doing <file op> on <file>"

// Returned when a nickname parameter expected for a command and isn't found.
#define ERR_NONICKNAMEGIVEN 431
#define ERR_NONICKNAMEGIVEN_MSG ":No nickname given"

// Returned after receiving a NICK message which contains characters which do not fall in the defined set. See section 2.3.1 for details on valid nicknames.
#define ERR_ERRONEUSNICKNAME 432
#define ERR_ERRONEUSNICKNAME_MSG "<nick> :Erroneous nickname"

// Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
#define ERR_NICKNAMEINUSE 433
#define ERR_NICKNAMEINUSE_MSG "<nick> :Nickname is already in use"

// Returned by a server to a client when it detects a nickname collision (registered of a NICK that already exists by another server).
#define ERR_NICKCOLLISION 436
#define ERR_NICKCOLLISION_MSG "<nick> :Nickname collision KILL from <user>@<host>"

// Returned by a server to a user trying to join a channel currently blocked by the channel delay mechanism.
// Returned by a server to a user trying to change nickname when the desired nickname is blocked by the nick delay mechanism.
#define ERR_UNAVAILRESOURCE 437
#define ERR_UNAVAILRESOURCE_MSG "<nick/channel> :Nick/channel is temporarily unavailable"

// Returned by the server to indicate that the target user of the command is not on the given channel.
#define ERR_USERNOTINCHANNEL 441
#define ERR_USERNOTINCHANNEL_MSG "<nick> <channel> :They aren't on that channel"

// Returned by the server whenever a client tries to perform a channel-affecting command for which the client isn't a member.
#define ERR_NOTONCHANNEL 442
#define ERR_NOTONCHANNEL_MSG "<channel> :You're not on that channel"

// Returned when a client tries to invite a user to a channel they are already on.
#define ERR_USERONCHANNEL 443
#define ERR_USERONCHANNEL_MSG "<user> <channel> :is already on channel"

// Returned by the summon after a SUMMON command for a user was unable to be performed since they were not logged in.
#define ERR_NOLOGIN 444
#define ERR_NOLOGIN_MSG "<user> :User not logged in"

// Returned as a response to the SUMMON command. MUST be returned by any server which doesn't implement it.
#define ERR_SUMMONDISABLED 445
#define ERR_SUMMONDISABLED_MSG ":SUMMON has been disabled"

// Returned as a response to the USERS command. MUST be returned by any server which does not implement it.
#define ERR_USERSDISABLED 446
#define ERR_USERSDISABLED_MSG ":USERS has been disabled"

// Returned by the server to indicate that the client MUST be registered before the server will allow it to be parsed in detail.
#define ERR_NOTREGISTERED 451
#define ERR_NOTREGISTERED_MSG ":You have not registered"

// Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.
#define ERR_NEEDMOREPARAMS 462
#define ERR_NEEDMOREPARAMS_MSG "<command> :Not enough parameters"

// Returned by the server to any link which tries to change part of the registered details (such as password or user details from second USER message).
#define ERR_ALREADYREGISTRED 462
#define ERR_ALREADYREGISTRED_MSG ":Unauthorized command (already registered)"

// Returned to a client which attempts to register with a server which does not been set up to allow connections from the host the attempted connection is tried.
#define ERR_NOPERMFORHOST 463
#define ERR_NOPERMFORHOST_MSG ":Your host isn't among the privileged"

// Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
#define ERR_PASSWDMISMATCH 464
#define ERR_PASSWDMISMATCH_MSG ":Password incorrect"

// Returned after an attempt to connect and register yourself with a server which has been set up to explicitly deny connections to you.
#define ERR_YOUREBANNEDCREEP 465
#define ERR_YOUREBANNEDCREEP_MSG ":You are banned from this server"

// Sent by a server to a user to inform that access to the server will soon be denied.
#define ERR_YOUWILLBEBANNED 466
#define ERR_YOUWILLBEBANNED_MSG "You will be banned from this server"

// Sent by a server to a user trying to change a channel mode for which they do not have the appropriate privileges.
#define ERR_CHANOPRIVSNEEDED 482
#define ERR_CHANOPRIVSNEEDED_MSG "<channel> :You're not channel operator"

// Any command requiring 'chanop' privileges (such as MODE messages) MUST return this error if the client making the attempt is not a chanop on the specified channel.
#define ERR_UNIQOPPRIVSNEEDED 485
#define ERR_UNIQOPPRIVSNEEDED_MSG ":You're not the original channel operator"

// If a client sends an OPER message and the server has not been configured to allow connections from the client's host as an operator, this error MUST be returned.
#define ERR_NOOPERHOST 491
#define ERR_NOOPERHOST_MSG ":No O-lines for your host"

// Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the mode flag sent was not recognized.
#define ERR_UMODEUNKNOWNFLAG 501
#define ERR_UMODEUNKNOWNFLAG_MSG ":Unknown MODE flag"

// Error sent to any user trying to view or change the user mode for a user other than themselves.
#define ERR_USERSDONTMATCH 502
#define ERR_USERSDONTMATCH_MSG ":Cannot change mode for other users"

#endif // IRC_ERROR_CODES_HPP
