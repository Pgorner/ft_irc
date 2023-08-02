/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:04:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/02 18:05:40 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERROR_CODES_HPP
#define IRC_ERROR_CODES_HPP

// Sent when a user tries to send a message to a nonexistent nickname.
#define ERR_NOSUCHNICK 401
#define ERR_NOSUCHNICK_MSG "No such nick/channel"

// Sent when a user tries to send a message to a nonexistent server.
#define ERR_NOSUCHSERVER 402
#define ERR_NOSUCHSERVER_MSG "No such server"

// Sent when a user tries to perform an action on a nonexistent channel.
#define ERR_NOSUCHCHANNEL 403
#define ERR_NOSUCHCHANNEL_MSG "No such channel"

// Sent when a user tries to send a message to a channel they are not a member of.
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_CANNOTSENDTOCHAN_MSG "Cannot send to channel"

// Sent when a user tries to join more channels than the server allows.
#define ERR_TOOMANYCHANNELS 405
#define ERR_TOOMANYCHANNELS_MSG "You have joined too many channels"

// Sent when a user tries to perform an action on a nickname that has not been registered.
#define ERR_WASNOSUCHNICK 406
#define ERR_WASNOSUCHNICK_MSG "There was no such nickname"

// Sent when a message is sent with too many recipients.
#define ERR_TOOMANYTARGETS 407
#define ERR_TOOMANYTARGETS_MSG "Duplicate recipients. No message delivered"

// Sent when a message is missing the "origin" (prefix) field.
#define ERR_NOORIGIN 409
#define ERR_NOORIGIN_MSG "No origin specified"

// Sent when a command is missing the recipient field (e.g., no target nickname or channel provided).
#define ERR_NORECIPIENT 411
#define ERR_NORECIPIENT_MSG "No recipient given"

// Sent when a user tries to send an empty message.
#define ERR_NOTEXTTOSEND 412
#define ERR_NOTEXTTOSEND_MSG "No text to send"

// Sent when an unknown or unsupported command is received.
#define ERR_UNKNOWNCOMMAND 421
#define ERR_UNKNOWNCOMMAND_MSG "Unknown command"

// Sent when a user tries to register with an empty nickname.
#define ERR_NONICKNAMEGIVEN 431
#define ERR_NONICKNAMEGIVEN_MSG "No nickname given"

// Sent when a user tries to register with an invalid nickname.
#define ERR_ERRONEUSNICKNAME 432
#define ERR_ERRONEUSNICKNAME_MSG "Erroneous nickname"

// Sent when a user tries to register with a nickname that is already in use.
#define ERR_NICKNAMEINUSE 433
#define ERR_NICKNAMEINUSE_MSG "Nickname is already in use"

// Sent when a user tries to perform an action on a channel they are not a member of.
#define ERR_NOTONCHANNEL 442
#define ERR_NOTONCHANNEL_MSG "You're not on that channel"

// Sent when a user tries to perform a command that requires registration before completing the registration process.
#define ERR_NOTREGISTERED 451
#define ERR_NOTREGISTERED_MSG "You have not registered"

// Sent when a user sends another registration command after successfully registering.
#define ERR_ALREADYREGISTRED 462
#define ERR_ALREADYREGISTRED_MSG "Unauthorized command (already registered)"

// Sent when a user tries to join a channel that has reached its maximum capacity.
#define ERR_CHANNELISFULL 471
#define ERR_CHANNELISFULL_MSG "Cannot join channel (+l)"

// Sent when a user tries to join an invite-only channel without an invitation.
#define ERR_INVITEONLYCHAN 473
#define ERR_INVITEONLYCHAN_MSG "Cannot join channel (+i)"

// Sent when a user is banned from a channel and attempts to join it.
#define ERR_BANNEDFROMCHAN 474
#define ERR_BANNEDFROMCHAN_MSG "Cannot join channel (+b)"

// Sent when a user tries to perform a privileged command without sufficient permissions.
#define ERR_NOPRIVILEGES 481
#define ERR_NOPRIVILEGES_MSG "Permission Denied- You're not an IRC operator"

// Sent when a user tries to perform an operation that requires channel operator privileges.
#define ERR_CHANOPRIVSNEEDED 482
#define ERR_CHANOPRIVSNEEDED_MSG "You're not channel operator"

#endif // IRC_ERROR_CODES_HPP
