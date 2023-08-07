/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:04:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/04 18:07:27 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "typography.hpp"
#include "irc.hpp"
#include "server.hpp"
#include <iostream>
#include <sstream>


namespace irc
{
    const std::string SERVERNAME = "YourServerName";

    /***********************************************
    RPL REPLIES
    ***********************************************/
    std::string RPL_WELCOME(const std::string& nick, const std::string& user, const std::string& host)
    {
        return ":" + SERVERNAME + " 001 Welcome to the Internet Relay Network\r\n" + nick + "!" + user + "@" + host + "\r\n";
    }

    std::string RPL_YOURHOST(const std::string& servername, const std::string& ver)
    {
        return ":" + SERVERNAME + " 002 Your host is " + servername + ", running version " + ver + "\r\n";
    }

    std::string RPL_CREATED(const std::string& date)
    {
        return ":" + SERVERNAME + " 003 This server was created " + date + "\r\n";
    }

    std::string RPL_MYINFO(const std::string& servername, const std::string& version, const std::string& available_user_modes, const std::string& available_channel_modes)
    {
        return ":" + SERVERNAME + " 004 " + servername + " " + version + " " + available_user_modes + " " + available_channel_modes + "\r\n";
    }

    std::string RPL_BOUNCE(const std::string& server_name, int port_number)
    {
        return ":" + SERVERNAME + " 005 Try server " + server_name + ", port " + std::to_string(port_number) + "\r\n";
    }

    std::string RPL_USERHOST(const std::string& reply, const std::vector<std::string>& replies)
    {
        std::string reply_str = ":" + SERVERNAME + " 302 :" + reply;
        for (const auto& r : replies)
        {
            reply_str += " " + r;
        }
        return reply_str + "\r\n";
    }

    std::string RPL_ISON(const std::vector<std::string>& nicknames)
    {
        std::string nick_list = ":";
        for (const auto& nick : nicknames)
        {
            nick_list += " " + nick;
        }
        return SERVERNAME + " 303 " + nick_list + "\r\n";
    }

    std::string RPL_AWAY(const std::string& nick, const std::string& away_message)
    {
        return ":" + SERVERNAME + " 301 " + nick + " :" + away_message + "\r\n";
    }

    std::string RPL_UNAWAY()
    {
        return ":" + SERVERNAME + " 305 :You are no longer marked as being away\r\n";
    }

    std::string RPL_NOWAWAY()
    {
        return ":" + SERVERNAME + " 306 :You have been marked as being away\r\n";
    }

    std::string RPL_WHOISUSER(const std::string& nick, const std::string& user, const std::string& host, const std::string& real_name)
    {
        return ":" + SERVERNAME + " 311 " + nick + " " + user + " " + host + " * :" + real_name + "\r\n";
    }

    std::string RPL_WHOISSERVER(const std::string& nick, const std::string& server, const std::string& server_info)
    {
        return ":" + SERVERNAME + " 312 " + nick + " " + server + " :" + server_info + "\r\n";
    }

    std::string RPL_WHOISOPERATOR(const std::string& nick)
    {
        return ":" + SERVERNAME + " 313 " + nick + " :is an IRC operator\r\n";
    }

    std::string RPL_WHOISIDLE(const std::string& nick, int seconds_idle)
    {
        return ":" + SERVERNAME + " 317 " + nick + " " + std::to_string(seconds_idle) + " :seconds idle\r\n";
    }

    std::string RPL_ENDOFWHOIS(const std::string& nick)
    {
        return ":" + SERVERNAME + " 318 " + nick + " :End of WHOIS list\r\n";
    }

    std::string RPL_WHOISCHANNELS(const std::string& nick, const std::vector<std::string>& channels)
    {
        std::string channel_list = ":";
        for (const auto& channel : channels)
        {
            channel_list += " " + channel;
        }
        return SERVERNAME + " 319 " + nick + " :" + channel_list + "\r\n";
    }

    std::string RPL_WHOWASUSER(const std::string& nick, const std::string& user, const std::string& host, const std::string& real_name)
    {
        return ":" + SERVERNAME + " 314 " + nick + " " + user + " " + host + " * :" + real_name + "\r\n";
    }

    std::string RPL_ENDOFWHOWAS(const std::string& nick)
    {
        return ":" + SERVERNAME + " 369 " + nick + " :End of WHOWAS\r\n";
    }

    std::string RPL_LISTSTART()
    {
        return ":" + SERVERNAME + " 321 Obsolete. Not used.\r\n";
    }

    std::string RPL_LIST(const std::string& channel, int num_visible, const std::string& topic)
    {
        return ":" + SERVERNAME + " 322 " + channel + " " + std::to_string(num_visible) + " :" + topic + "\r\n";
    }

    std::string RPL_LISTEND()
    {
        return ":" + SERVERNAME + " 323 :End of LIST\r\n";
    }

    std::string RPL_UNIQOPIS(const std::string& channel, const std::string& nickname)
    {
        return ":" + SERVERNAME + " 325 " + channel + " " + nickname + "\r\n";
    }

    std::string RPL_CHANNELMODEIS(const std::string& channel, const std::string& mode, const std::string& mode_params)
    {
        return ":" + SERVERNAME + " 324 " + channel + " " + mode + " " + mode_params + "\r\n";
    }

    std::string RPL_NOTOPIC(const std::string& channel)
    {
        return ":" + SERVERNAME + " 331 " + channel + " :No topic is set\r\n";
    }

    std::string RPL_TOPIC(const std::string& channel, const std::string& topic)
    {
        return ":" + SERVERNAME + " 332 " + channel + " :" + topic + "\r\n";
    }

    std::string RPL_INVITING(const std::string& channel, const std::string& nick)
    {
        return ":" + SERVERNAME + " 341 " + channel + " " + nick + "\r\n";
    }

    std::string RPL_SUMMONING(const std::string& user)
    {
        return ":" + SERVERNAME + " 342 " + user + " :Summoning user to IRC\r\n";
    }

    std::string RPL_INVITELIST(const std::string& channel, const std::string& invitemask)
    {
        return ":" + SERVERNAME + " 346 " + channel + " " + invitemask + "\r\n";
    }

    std::string RPL_ENDOFINVITELIST(const std::string& channel)
    {
        return ":" + SERVERNAME + " 347 " + channel + " :End of channel invite list\r\n";
    }

    std::string RPL_EXCEPTLIST(const std::string& channel, const std::string& exceptionmask)
    {
        return ":" + SERVERNAME + " 348 " + channel + " " + exceptionmask + "\r\n";
    }

    std::string RPL_ENDOFEXCEPTLIST(const std::string& channel)
    {
        return ":" + SERVERNAME + " 349 " + channel + " :End of channel exception list\r\n";
    }

    std::string RPL_VERSION(const std::string& version, const std::string& server, const std::string& comments)
    {
        return ":" + SERVERNAME + " 351 " + version + " " + server + " :" + comments + "\r\n";
    }

    std::string RPL_WHOREPLY(const std::string& channel, const std::string& user, const std::string& host, const std::string& server, const std::string& nick, const std::string& hopcount, const std::string& real_name)
    {
        return ":" + SERVERNAME + " 352 " + channel + " " + user + " " + host + " " + server + " " + nick + " H" + hopcount + " : " + real_name + "\r\n";
    }

    std::string RPL_ENDOFWHO(const std::string& name)
    {
        return ":" + SERVERNAME + " 315 " + name + " :End of WHO list\r\n";
    }

    std::string RPL_NAMREPLY(const std::string& channel, const std::string& nick_list)
    {
        return ":" + SERVERNAME + " 353 = " + channel + " :" + nick_list + "\r\n";
    }

    std::string RPL_ENDOFNAMES(const std::string& channel)
    {
        return ":" + SERVERNAME + " 366 " + channel + " :End of NAMES list\r\n";
    }

    std::string RPL_LINKS(const std::string& mask, const std::string& server, const std::string& hopcount, const std::string& server_info)
    {
        return ":" + SERVERNAME + " 364 " + mask + " " + server + " :" + hopcount + " " + server_info + "\r\n";
    }

    std::string RPL_ENDOFLINKS(const std::string& mask)
    {
        return ":" + SERVERNAME + " 365 " + mask + " :End of LINKS list\r\n";
    }

    std::string RPL_BANLIST(const std::string& channel, const std::string& banmask)
    {
        return ":" + SERVERNAME + " 367 " + channel + " " + banmask + "\r\n";
    }

    std::string RPL_ENDOFBANLIST(const std::string& channel)
    {
        return ":" + SERVERNAME + " 368 " + channel + " :End of channel ban list\r\n";
    }

    std::string RPL_INFO(const std::string& info)
    {
        return ":" + SERVERNAME + " 371 :" + info + "\r\n";
    }

    std::string RPL_ENDOFINFO()
    {
        return ":" + SERVERNAME + " 374 :End of INFO list\r\n";
    }

    std::string RPL_MOTDSTART(const std::string& server)
    {
        return ":" + SERVERNAME + " 375 :- " + server + " Message of the day - \r\n";
    }

    std::string RPL_MOTD(const std::string& text)
    {
        return ":" + SERVERNAME + " 372 :- " + text + "\r\n";
    }

    std::string RPL_ENDOFMOTD()
    {
        return ":" + SERVERNAME + " 376 :End of MOTD command\r\n";
    }

    std::string RPL_YOUREOPER()
    {
        return ":" + SERVERNAME + " 381 :You are now an IRC operator\r\n";
    }

    std::string RPL_REHASHING(const std::string& config_file)
    {
        return ":" + SERVERNAME + " 382 " + config_file + " :Rehashing\r\n";
    }

    std::string RPL_YOURESERVICE(const std::string& servicename)
    {
        return ":" + SERVERNAME + " 383 You are service " + servicename + "\r\n";
    }

    std::string RPL_TIME(const std::string& server, const std::string& time)
    {
        return ":" + SERVERNAME + " 391 " + server + " :" + time + "\r\n";
    }

    std::string RPL_USERSSTART()
    {
        return ":" + SERVERNAME + " 392 :UserID   Terminal  Host\r\n";
    }

    std::string RPL_USERS(const std::string& username, const std::string& ttyline, const std::string& hostname)
    {
        return ":" + SERVERNAME + " 393 :" + username + " " + ttyline + " " + hostname + "\r\n";
    }

    std::string RPL_ENDOFUSERS()
    {
        return ":" + SERVERNAME + " 394 :End of users\r\n";
    }

    std::string RPL_NOUSERS()
    {
        return ":" + SERVERNAME + " 395 :Nobody logged in\r\n";
    }

    std::string RPL_TRACELINK(const std::string& version_debug, const std::string& destination, const std::string& next_server, const std::string& protocol_version, const std::string& link_uptime, const std::string& backstream_sendq, const std::string& upstream_sendq)
    {
        return ":" + SERVERNAME + " 200 Link " + version_debug + " " + destination + " " + next_server + " V" + protocol_version + " " + link_uptime + " " + backstream_sendq + " " + upstream_sendq + "\r\n";
    }

    std::string RPL_TRACECONNECTING(const std::string& irc_class, const std::string& server)
    {
        return ":" + SERVERNAME + " 201 Try. " + irc_class + " " + server + "\r\n";
    }

    std::string RPL_TRACEHANDSHAKE(const std::string& irc_class, const std::string& server)
    {
        return ":" + SERVERNAME + " 202 H.S. " + irc_class + " " + server + "\r\n";
    }

    std::string RPL_TRACEUNKNOWN(const std::string& irc_class, const std::string& client_ip)
    {
        return ":" + SERVERNAME + " 203 ???? " + irc_class + " [" + client_ip + "]\r\n";
    }

    std::string RPL_TRACEOPERATOR(const std::string& irc_class, const std::string& nick)
    {
        return ":" + SERVERNAME + " 204 Oper " + irc_class + " " + nick + "\r\n";
    }

    std::string RPL_TRACEUSER(const std::string& irc_class, const std::string& nick)
    {
        return ":" + SERVERNAME + " 205 User " + irc_class + " " + nick + "\r\n";
    }

    std::string RPL_TRACESERVER(const std::string& irc_class, const std::string& intS, const std::string& intC, const std::string& server, const std::string& user_host, const std::string& protocol_version)
    {
        return ":" + SERVERNAME + " 206 Serv " + irc_class + " " + intS + " " + intC + " " + server + " " + user_host + " V" + protocol_version + "\r\n";
    }

    std::string RPL_TRACESERVICE(const std::string& irc_class, const std::string& name, const std::string& type, const std::string& active_type)
    {
        return ":" + SERVERNAME + " 207 Service " + irc_class + " " + name + " " + type + " " + active_type + "\r\n";
    }

    std::string RPL_TRACENEWTYPE(const std::string& newtype, const std::string& client_name)
    {
        return ":" + SERVERNAME + " 208 " + newtype + " 0 " + client_name + "\r\n";
    }

    std::string RPL_TRACECLASS(const std::string& irc_class, const std::string& count)
    {
        return ":" + SERVERNAME + " 209 Class " + irc_class + " " + count + "\r\n";
    }

    std::string RPL_TRACERECONNECT()
    {
        return ":" + SERVERNAME + " 210 Unused.\r\n";
    }

    std::string RPL_TRACELOG(const std::string& logfile, const std::string& debug_level)
    {
        return ":" + SERVERNAME + " 261 File " + logfile + " " + debug_level + "\r\n";
    }

    std::string RPL_TRACEEND(const std::string& server_name, const std::string& version_debug)
    {
        return ":" + SERVERNAME + " 262 " + server_name + " " + version_debug + " :End of TRACE\r\n";
    }

    std::string RPL_STATSLINKINFO(const std::string& linkname, const std::string& sendq, const std::string& sent_messages, const std::string& sent_kbytes, const std::string& received_messages, const std::string& received_kbytes, const std::string& time_open)
    {
        return ":" + SERVERNAME + " 211 " + linkname + " " + sendq + " " + sent_messages + " " + sent_kbytes + " " + received_messages + " " + received_kbytes + " " + time_open + "\r\n";
    }

    std::string RPL_STATSCOMMANDS(const std::string& command, const std::string& count, const std::string& byte_count, const std::string& remote_count)
    {
        return ":" + SERVERNAME + " 212 " + command + " " + count + " " + byte_count + " " + remote_count + "\r\n";
    }

    std::string RPL_ENDOFSTATS(const std::string& stats_letter)
    {
        return ":" + SERVERNAME + " 219 " + stats_letter + " :End of STATS report\r\n";
    }

    std::string RPL_STATSUPTIME(int days, int hours, int minutes, int seconds)
    {
        return ":" + SERVERNAME + " 242 :Server Up " + std::to_string(days) + " days " + std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + "\r\n";
    }

    std::string RPL_STATSOLINE(const std::string& hostmask, const std::string& name)
    {
        return ":" + SERVERNAME + " 243 O " + hostmask + " * " + name + "\r\n";
    }

    std::string RPL_UMODEIS(const std::string& user_mode_string)
    {
        return ":" + SERVERNAME + " 221 " + user_mode_string + "\r\n";
    }

    std::string RPL_SERVLIST(const std::string& name, const std::string& server, const std::string& mask, const std::string& type, const std::string& hopcount, const std::string& info)
    {
        return ":" + SERVERNAME + " 234 " + name + " " + server + " " + mask + " " + type + " " + hopcount + " " + info + "\r\n";
    }

    std::string RPL_SERVLISTEND(const std::string& mask, const std::string& type)
    {
        return ":" + SERVERNAME + " 235 " + mask + " " + type + " :End of service listing\r\n";
    }

    std::string RPL_LUSERCLIENT(const std::string& num_users, const std::string& num_services, const std::string& num_servers)
    {
        return ":" + SERVERNAME + " 251 :There are " + num_users + " users and " + num_services + " services on " + num_servers + " servers\r\n";
    }

    std::string RPL_LUSEROP(const std::string& num_operators)
    {
        return ":" + SERVERNAME + " 252 " + num_operators + " :operator(s) online\r\n";
    }

    std::string RPL_LUSERUNKNOWN(const std::string& num_unknown)
    {
        return ":" + SERVERNAME + " 253 " + num_unknown + " :unknown connection(s)\r\n";
    }

    std::string RPL_LUSERCHANNELS(const std::string& num_channels)
    {
        return ":" + SERVERNAME + " 254 " + num_channels + " :channels formed\r\n";
    }

    std::string RPL_LUSERME(const std::string& num_clients, const std::string& num_servers)
    {
        return ":" + SERVERNAME + " 255 :I have " + num_clients + " clients and " + num_servers + " servers\r\n";
    }

    std::string RPL_ADMINME(const std::string& server_name)
    {
        return ":" + SERVERNAME + " 256 " + server_name + " :Administrative info\r\n";
    }

    std::string RPL_ADMINLOC1(const std::string& admin_info)
    {
        return ":" + SERVERNAME + " 257 :Location " + admin_info + "\r\n";
    }

    std::string RPL_ADMINLOC2(const std::string& admin_info)
    {
        return ":" + SERVERNAME + " 258 :Location " + admin_info + "\r\n";
    }

    std::string RPL_ADMINEMAIL(const std::string& admin_email)
    {
        return ":" + SERVERNAME + " 259 :Email " + admin_email + "\r\n";
    }

    std::string RPL_TRYAGAIN(const std::string& command)
    {
        return ":" + SERVERNAME + " 263 " + command + " :Please wait a while and try again\r\n";
    }
}

#endif 