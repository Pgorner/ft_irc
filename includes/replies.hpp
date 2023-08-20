/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:04:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/20 18:21:52 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP
#include "typography.hpp"
#include <iostream>
#include <sstream>

namespace irc
{
        /***********************************************
    ERROR REPLIES
    ***********************************************/
    const char* ERR_NOSUCHNICK(const std::string& nickname, const std::string& channel);
    const char* ERR_NOSUCHSERVER(const std::string& server_name);
    const char* ERR_NOSUCHCHANNEL(const std::string& channel_name);
    const char* ERR_CANNOTSENDTOCHAN(const std::string& channel_name);
    const char* ERR_TOOMANYCHANNELS(const std::string& channel_name);
    const char* ERR_WASNOSUCHNICK(const std::string& nickname);
    const char* ERR_TOOMANYTARGETS(const std::string& target, const std::string& error_code, const std::string& abort_message);
    const char* ERR_NOSUCHSERVICE(const std::string& service_name);
    const char* ERR_NOORIGIN();
    const char* ERR_NORECIPIENT();
    const char* ERR_NOTEXTTOSEND();
    const char* ERR_NOTOPLEVEL(const std::string& mask);
    const char* ERR_WILDTOPLEVEL(const std::string& mask);
    const char* ERR_BADMASK(const std::string& mask);
    const char* ERR_UNKNOWNCOMMAND(const std::string& command);
    const char* ERR_NOMOTD();
    const char* ERR_NOADMININFO(const std::string& server);
    const char* ERR_FILEERROR(const std::string& file_op, const std::string& file);
    const char* ERR_NONICKNAMEGIVEN();
    const char* ERR_ERRONEUSNICKNAME(const std::string& nick);
    const char* ERR_NICKNAMEINUSE(const std::string& nick);
    const char* ERR_NICKCOLLISION(const std::string& nick, const std::string& user, const std::string& host);
    const char* ERR_UNAVAILRESOURCE(const std::string& channel);
    const char* ERR_USERNOTINCHANNEL(const std::string& nick, const std::string& channel);
    const char* ERR_NOTONCHANNEL(const std::string& channel);
    const char* ERR_USERONCHANNEL(const std::string& nick, const std::string& channel);
    const char* ERR_NOLOGIN(const std::string& user);
    const char* ERR_SUMMONDISABLED();
    const char* ERR_USERSDISABLED();
    const char* ERR_NOTREGISTERED();
    const char* ERR_NEEDMOREPARAMS(const std::string& command);
    const char* ERR_ALREADYREGISTRED();
    const char* ERR_NOPERMFORHOST();
    const char* ERR_PASSWDMISMATCH();
    const char* ERR_YOUREBANNEDCREEP();
    const char* ERR_KEYSET(const std::string& channel);
    const char* ERR_CHANNELISFULL(const std::string& channel);
    const char* ERR_UNKNOWNMODE(const std::string& mode_char);
    const char* ERR_INVITEONLYCHAN(const std::string& channel);
    const char* ERR_BANNEDFROMCHAN(const std::string& channel);
    const char* ERR_BADCHANNELKEY(const std::string& channel);
    const char* ERR_NOPRIVILEGES();
    const char* ERR_CHANOPRIVSNEEDED(const std::string& channel);
    const char* ERR_CANTKILLSERVER();
    const char* ERR_NOOPERHOST();
    const char* ERR_UMODEUNKNOWNFLAG();
    const char* ERR_USERSDONTMATCH();
    /***********************************************
    RPL REPLIES
    ***********************************************/
    const char* RPL_WELCOME(const std::string& nick, const std::string& user, const std::string& host);
    const char* RPL_YOURHOST(const std::string& version);
    const char* RPL_CREATED(const std::string& date);
    const char* RPL_MYINFO(const std::string& version, const std::string& available_user_modes, const std::string& available_channel_modes);
    const char* RPL_BOUNCE(const std::string& server_name, int port_number);
    const char* RPL_USERHOST(const std::string& reply, const std::vector<std::string>& replies);
    const char* RPL_ISON(const std::vector<std::string>& nicknames);
    const char* RPL_AWAY(const std::string& nick, const std::string& away_message);
    const char* RPL_UNAWAY();
    const char* RPL_NOWAWAY();
    const char* RPL_WHOISUSER(const std::string& nick, const std::string& user, const std::string& host, const std::string& real_name);
    const char* RPL_WHOISSERVER(const std::string& nick, const std::string& server, const std::string& server_info);
    const char* RPL_WHOISOPERATOR(const std::string& nick);
    const char* RPL_WHOISIDLE(const std::string& nick, int seconds_idle);
    const char* RPL_ENDOFWHOIS(const std::string& nick);
    const char* RPL_WHOISCHANNELS(const std::string& nick, const std::vector<std::string>& channels);
    const char* RPL_WHOWASUSER(const std::string& nick, const std::string& user, const std::string& host, const std::string& real_name);
    const char* RPL_ENDOFWHOWAS(const std::string& nick);
    const char* RPL_LISTSTART();
    const char* RPL_LIST(const std::string& channel, int num_visible, const std::string& topic);
    const char* RPL_LISTEND();
    const char* RPL_UNIQOPIS(const std::string& channel, const std::string& nickname);
    const char* RPL_CHANNELMODEIS(const std::string& channel, const std::string& mode, const std::string& mode_params);
    const char* RPL_NOTOPIC(const std::string& channel);
    const char* RPL_TOPIC(const std::string& channel, const std::string& topic);
    const char* RPL_INVITING(const std::string& channel, const std::string& nick);
    const char* RPL_SUMMONING(const std::string& user);
    const char* RPL_INVITELIST(const std::string& channel, const std::string& invitemask);
    const char* RPL_ENDOFINVITELIST(const std::string& channel);
    const char* RPL_EXCEPTLIST(const std::string& channel, const std::string& exceptionmask);
    const char* RPL_ENDOFEXCEPTLIST(const std::string& channel);
    const char* RPL_VERSION(const std::string& version, const std::string& server, const std::string& comments);
    const char* RPL_WHOREPLY(const std::string& channel, const std::string& user, const std::string& host, const std::string& server, const std::string& nick, const std::string& hopcount, const std::string& real_name);
    const char* RPL_ENDOFWHO(const std::string& name);
    const char* RPL_NAMREPLY(const std::string& channel, const std::string& nick_list);
    const char* RPL_ENDOFNAMES(const std::string& channel);
    const char* RPL_LINKS(const std::string& mask, const std::string& server, const std::string& hopcount, const std::string& server_info);
    const char* RPL_ENDOFLINKS(const std::string& mask);
    const char* RPL_BANLIST(const std::string& channel, const std::string& banmask);
    const char* RPL_ENDOFBANLIST(const std::string& channel);
    const char* RPL_INFO(const std::string& info);
    const char* RPL_ENDOFINFO();
    const char* RPL_MOTDSTART(const std::string& server);
    const char* RPL_MOTD(const std::string& text);
    const char* RPL_ENDOFMOTD();
    const char* RPL_YOUREOPER();
    const char* RPL_REHASHING(const std::string& config_file);
    const char* RPL_YOURESERVICE(const std::string& servicename);
    const char* RPL_TIME(const std::string& server, const std::string& time);
    const char* RPL_USERSSTART();
    const char* RPL_USERS(const std::string& username, const std::string& ttyline, const std::string& hostname);
    const char* RPL_ENDOFUSERS();
    const char* RPL_NOUSERS();
    const char* RPL_TRACELINK(const std::string& version_debug, const std::string& destination, const std::string& next_server, const std::string& protocol_version, const std::string& link_uptime, const std::string& backstream_sendq, const std::string& upstream_sendq);
    const char* RPL_TRACECONNECTING(const std::string& irc_class, const std::string& server);
    const char* RPL_TRACEHANDSHAKE(const std::string& irc_class, const std::string& server);
    const char* RPL_TRACEUNKNOWN(const std::string& irc_class, const std::string& client_ip);
    const char* RPL_TRACEOPERATOR(const std::string& irc_class, const std::string& nick);
    const char* RPL_TRACEUSER(const std::string& irc_class, const std::string& nick);
    const char* RPL_TRACESERVER(const std::string& irc_class, const std::string& intS, const std::string& intC, const std::string& server, const std::string& user_host, const std::string& protocol_version);
    const char* RPL_TRACESERVICE(const std::string& irc_class, const std::string& name, const std::string& type, const std::string& active_type);
    const char* RPL_TRACENEWTYPE(const std::string& newtype, const std::string& client_name);
    const char* RPL_TRACECLASS(const std::string& irc_class, const std::string& count);
    const char* RPL_TRACERECONNECT();
    const char* RPL_TRACELOG(const std::string& logfile, const std::string& debug_level);
    const char* RPL_TRACEEND(const std::string& server_name, const std::string& version_debug);
    const char* RPL_STATSLINKINFO(const std::string& linkname, const std::string& sendq, const std::string& sent_messages, const std::string& sent_kbytes, const std::string& received_messages, const std::string& received_kbytes, const std::string& time_open);
    const char* RPL_STATSCOMMANDS(const std::string& command, const std::string& count, const std::string& byte_count, const std::string& remote_count);
    const char* RPL_ENDOFSTATS(const std::string& stats_letter);
    const char* RPL_STATSUPTIME(int days, int hours, int minutes, int seconds);
    const char* RPL_STATSOLINE(const std::string& hostmask, const std::string& name);
    const char* RPL_UMODEIS(const std::string& user_mode_string);
    const char* RPL_SERVLIST(const std::string& name, const std::string& server, const std::string& mask, const std::string& type, const std::string& hopcount, const std::string& info);
    const char* RPL_SERVLISTEND(const std::string& mask, const std::string& type);
    const char* RPL_LUSERCLIENT(const std::string& num_users, const std::string& num_services, const std::string& num_servers);
    const char* RPL_LUSEROP(const std::string& num_operators);
    const char* RPL_LUSERUNKNOWN(const std::string& num_unknown);
    const char* RPL_LUSERCHANNELS(const std::string& num_channels);
    const char* RPL_LUSERME(const std::string& num_clients, const std::string& num_servers);
    const char* RPL_ADMINME(const std::string& server_name);
    const char* RPL_ADMINLOC1(const std::string& admin_info);
    const char* RPL_ADMINLOC2(const std::string& admin_info);
    const char* RPL_ADMINEMAIL(const std::string& admin_email);
    const char* RPL_TRYAGAIN(const std::string& command);
}
#endif 