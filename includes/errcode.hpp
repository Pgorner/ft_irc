/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:04:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 15:05:41 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERROR_CODES_HPP
#define IRC_ERROR_CODES_HPP

// Sent when a user tries to send a message to a nonexistent nickname.
#define ERR_NOSUCHNICK 401

// Sent when a user tries to send a message to a nonexistent server.
#define ERR_NOSUCHSERVER 402

// Sent when a user tries to perform an action on a nonexistent channel.
#define ERR_NOSUCHCHANNEL 403

// Sent when a user tries to send a message to a channel they are not a member of.
#define ERR_CANNOTSENDTOCHAN 404

// Sent when a user tries to join more channels than the server allows.
#define ERR_TOOMANYCHANNELS 405

// Sent when a user tries to perform an action on a nickname that has not been registered.
#define ERR_WASNOSUCHNICK 406

// Sent when a message is sent with too many recipients.
#define ERR_TOOMANYTARGETS 407

// Sent when a message is missing the "origin" (prefix) field.
#define ERR_NOORIGIN 409

// Sent when a command is missing the recipient field (e.g., no target nickname or channel provided).
#define ERR_NORECIPIENT 411

// Sent when a user tries to send an empty message.
#define ERR_NOTEXTTOSEND 412

// Sent when an unknown or unsupported command is received.
#define ERR_UNKNOWNCOMMAND 421

// Sent when a user tries to register with an empty nickname.
#define ERR_NONICKNAMEGIVEN 431

// Sent when a user tries to register with an invalid nickname.
#define ERR_ERRONEUSNICKNAME 432

// Sent when a user tries to register with a nickname that is already in use.
#define ERR_NICKNAMEINUSE 433

// Sent when a user tries to perform an action on a channel they are not a member of.
#define ERR_NOTONCHANNEL 442

// Sent when a user tries to perform a command that requires registration before completing the registration process.
#define ERR_NOTREGISTERED 451

// Sent when a user sends another registration command after successfully registering.
#define ERR_ALREADYREGISTRED 462

// Sent when a user tries to join a channel that has reached its maximum capacity.
#define ERR_CHANNELISFULL 471

// Sent when a user tries to join an invite-only channel without an invitation.
#define ERR_INVITEONLYCHAN 473

// Sent when a user is banned from a channel and attempts to join it.
#define ERR_BANNEDFROMCHAN 474

// Sent when a user tries to perform a privileged command without sufficient permissions.
#define ERR_NOPRIVILEGES 481

// Sent when a user tries to perform an operation that requires channel operator privileges.
#define ERR_CHANOPRIVSNEEDED 482

#endif // IRC_ERROR_CODES_HPP
