/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:04:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/08 18:56:24 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// RPL_WELCOME
#define RPL_WELCOME 001
#define RPL_WELCOME_MSG "Welcome to the Internet Relay Network\r\n<nick>!<user>@<host>"

// RPL_YOURHOST
#define RPL_YOURHOST 002
#define RPL_YOURHOST_MSG "Your host is <servername>, running version <ver>"

// RPL_CREATED
#define RPL_CREATED 003
#define RPL_CREATED_MSG "This server was created <date>"

// RPL_MYINFO
#define RPL_MYINFO 004
#define RPL_MYINFO_MSG "<servername> <version> <available user modes> <available channel modes>"

// RPL_BOUNCE
#define RPL_BOUNCE 005
#define RPL_BOUNCE_MSG "Try server <server name>, port <port number>"

// RPL_USERHOST
#define RPL_USERHOST 302
#define RPL_USERHOST_MSG ":*1<reply> *( " " <reply> )"

// RPL_ISON
#define RPL_ISON 303
#define RPL_ISON_MSG ":*1<nick> *( " " <nick> )"

// RPL_AWAY
#define RPL_AWAY 301
#define RPL_AWAY_MSG "<nick> :<away message>"

// RPL_UNAWAY
#define RPL_UNAWAY 305
#define RPL_UNAWAY_MSG ":You are no longer marked as being away"

// RPL_NOWAWAY
#define RPL_NOWAWAY 306
#define RPL_NOWAWAY_MSG ":You have been marked as being away"

// RPL_WHOISUSER
#define RPL_WHOISUSER 311
#define RPL_WHOISUSER_MSG "<nick> <user> <host> * :<real name>"

// RPL_WHOISSERVER
#define RPL_WHOISSERVER 312
#define RPL_WHOISSERVER_MSG "<nick> <server> :<server info>"

// RPL_WHOISOPERATOR
#define RPL_WHOISOPERATOR 313
#define RPL_WHOISOPERATOR_MSG "<nick> :is an IRC operator"

// RPL_WHOISIDLE
#define RPL_WHOISIDLE 317
#define RPL_WHOISIDLE_MSG "<nick> <integer> :seconds idle"

// RPL_ENDOFWHOIS
#define RPL_ENDOFWHOIS 318
#define RPL_ENDOFWHOIS_MSG "<nick> :End of WHOIS list"

// RPL_WHOISCHANNELS
#define RPL_WHOISCHANNELS 319
#define RPL_WHOISCHANNELS_MSG "<nick> :*( ( "@" / "+" ) <channel> " " )"

// RPL_WHOWASUSER
#define RPL_WHOWASUSER 314
#define RPL_WHOWASUSER_MSG "<nick> <user> <host> * :<real name>"

// RPL_ENDOFWHOWAS
#define RPL_ENDOFWHOWAS 369
#define RPL_ENDOFWHOWAS_MSG "<nick> :End of WHOWAS"

// RPL_LISTSTART
#define RPL_LISTSTART 321
#define RPL_LISTSTART_MSG "Obsolete. Not used."

// RPL_LIST
#define RPL_LIST 322
#define RPL_LIST_MSG "<channel> <# visible> :<topic>"

// RPL_LISTEND
#define RPL_LISTEND 323
#define RPL_LISTEND_MSG ":End of LIST"

// RPL_UNIQOPIS
#define RPL_UNIQOPIS 325
#define RPL_UNIQOPIS_MSG "<channel> <nickname>"

// RPL_CHANNELMODEIS
#define RPL_CHANNELMODEIS 324
#define RPL_CHANNELMODEIS_MSG "<channel> <mode> <mode params>"

// RPL_NOTOPIC
#define RPL_NOTOPIC 331
#define RPL_NOTOPIC_MSG "<channel> :No topic is set"

// RPL_TOPIC
#define RPL_TOPIC 332
#define RPL_TOPIC_MSG "<channel> :<topic>"

// RPL_INVITING
#define RPL_INVITING 341
#define RPL_INVITING_MSG "<channel> <nick>"

// RPL_SUMMONING
#define RPL_SUMMONING 342
#define RPL_SUMMONING_MSG "<user> :Summoning user to IRC"

// RPL_INVITELIST
#define RPL_INVITELIST 346
#define RPL_INVITELIST_MSG "<channel> <invitemask>"

// RPL_ENDOFINVITELIST
#define RPL_ENDOFINVITELIST 347
#define RPL_ENDOFINVITELIST_MSG "<channel> :End of channel invite list"

// RPL_EXCEPTLIST
#define RPL_EXCEPTLIST 348
#define RPL_EXCEPTLIST_MSG "<channel> <exceptionmask>"

// RPL_ENDOFEXCEPTLIST
#define RPL_ENDOFEXCEPTLIST 349
#define RPL_ENDOFEXCEPTLIST_MSG "<channel> :End of channel exception list"

// RPL_VERSION
#define RPL_VERSION 351
#define RPL_VERSION_MSG "<version>.<debuglevel> <server> :<comments>"

// RPL_WHOREPLY
#define RPL_WHOREPLY 352
#define RPL_WHOREPLY_MSG "<channel> <user> <host> <server> <nick> ( \"H\" / \"G\" > [\"*\"] [ ( \"@\" / \"+\" ) ] :<hopcount> <real name>"

// RPL_ENDOFWHO
#define RPL_ENDOFWHO 315
#define RPL_ENDOFWHO_MSG "<name> :End of WHO list"

// RPL_NAMREPLY
#define RPL_NAMREPLY 353
#define RPL_NAMREPLY_MSG "( \"=\" / \"*\" / \"@\" ) <channel> :[ \"@\" / \"+\" ] <nick> *( \" \" [ \"@\" / \"+\" ] <nick> )"

// RPL_ENDOFNAMES
#define RPL_ENDOFNAMES 366
#define RPL_ENDOFNAMES_MSG "<channel> :End of NAMES list"

// RPL_LINKS
#define RPL_LINKS 364
#define RPL_LINKS_MSG "<mask> <server> :<hopcount> <server info>"

// RPL_ENDOFLINKS
#define RPL_ENDOFLINKS 365
#define RPL_ENDOFLINKS_MSG "<mask> :End of LINKS list"

// RPL_BANLIST
#define RPL_BANLIST 367
#define RPL_BANLIST_MSG "<channel> <banmask>"

// RPL_ENDOFBANLIST
#define RPL_ENDOFBANLIST 368
#define RPL_ENDOFBANLIST_MSG "<channel> :End of channel ban list"

// RPL_INFO
#define RPL_INFO 371
#define RPL_INFO_MSG ":<string>"

// RPL_ENDOFINFO
#define RPL_ENDOFINFO 374
#define RPL_ENDOFINFO_MSG ":End of INFO list"

// RPL_MOTDSTART
#define RPL_MOTDSTART 375
#define RPL_MOTDSTART_MSG ":- <server> Message of the day - "

// RPL_MOTD
#define RPL_MOTD 372
#define RPL_MOTD_MSG ":- <text>"

// RPL_ENDOFMOTD
#define RPL_ENDOFMOTD 376
#define RPL_ENDOFMOTD_MSG ":End of MOTD command"

// RPL_YOUREOPER
#define RPL_YOUREOPER 381
#define RPL_YOUREOPER_MSG ":You are now an IRC operator"

// RPL_REHASHING
#define RPL_REHASHING 382
#define RPL_REHASHING_MSG "<config file> :Rehashing"

// RPL_YOURESERVICE
#define RPL_YOURESERVICE 383
#define RPL_YOURESERVICE_MSG "You are service <servicename>"

// RPL_TIME
#define RPL_TIME 391
#define RPL_TIME_MSG "<server> :<string showing server's local time>"

// RPL_USERSSTART
#define RPL_USERSSTART 392
#define RPL_USERSSTART_MSG ":UserID   Terminal  Host"

// RPL_USERS
#define RPL_USERS 393
#define RPL_USERS_MSG ":<username> <ttyline> <hostname>"

// RPL_ENDOFUSERS
#define RPL_ENDOFUSERS 394
#define RPL_ENDOFUSERS_MSG ":End of users"

// RPL_NOUSERS
#define RPL_NOUSERS 395
#define RPL_NOUSERS_MSG ":Nobody logged in"

// RPL_TRACE* Messages
#define RPL_TRACELINK 200
#define RPL_TRACELINK_MSG "Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>"

#define RPL_TRACECONNECTING 201
#define RPL_TRACECONNECTING_MSG "Try. <class> <server>"

#define RPL_TRACEHANDSHAKE 202
#define RPL_TRACEHANDSHAKE_MSG "H.S. <class> <server>"

#define RPL_TRACEUNKNOWN 203
#define RPL_TRACEUNKNOWN_MSG "???? <class> [<client IP address in dot form>]"

#define RPL_TRACEOPERATOR 204
#define RPL_TRACEOPERATOR_MSG "Oper <class> <nick>"

#define RPL_TRACEUSER 205
#define RPL_TRACEUSER_MSG "User <class> <nick>"

#define RPL_TRACESERVER 206
#define RPL_TRACESERVER_MSG "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>"

#define RPL_TRACESERVICE 207
#define RPL_TRACESERVICE_MSG "Service <class> <name> <type> <active type>"

#define RPL_TRACENEWTYPE 208
#define RPL_TRACENEWTYPE_MSG "<newtype> 0 <client name>"

#define RPL_TRACECLASS 209
#define RPL_TRACECLASS_MSG "Class <class> <count>"

#define RPL_TRACERECONNECT 210
#define RPL_TRACERECONNECT_MSG "Unused."

#define RPL_TRACELOG 261
#define RPL_TRACELOG_MSG "File <logfile> <debug level>"

#define RPL_TRACEEND 262
#define RPL_TRACEEND_MSG "<server name> <version & debug level> :End of TRACE"

// RPL_STATSLINKINFO
#define RPL_STATSLINKINFO 211
#define RPL_STATSLINKINFO_MSG "<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>"

// RPL_STATSCOMMANDS
#define RPL_STATSCOMMANDS 212
#define RPL_STATSCOMMANDS_MSG "<command> <count> <byte count> <remote count>"

// RPL_ENDOFSTATS
#define RPL_ENDOFSTATS 219
#define RPL_ENDOFSTATS_MSG "<stats letter> :End of STATS report"

// RPL_STATSUPTIME
#define RPL_STATSUPTIME 242
#define RPL_STATSUPTIME_MSG ":Server Up %d days %d:%02d:%02d"

// RPL_STATSOLINE
#define RPL_STATSOLINE 243
#define RPL_STATSOLINE_MSG "O <hostmask> * <name>"

// RPL_UMODEIS
#define RPL_UMODEIS 221
#define RPL_UMODEIS_MSG "<user mode string>"

// RPL_SERVLIST
#define RPL_SERVLIST 234
#define RPL_SERVLIST_MSG "<name> <server> <mask> <type> <hopcount> <info>"

// RPL_SERVLISTEND
#define RPL_SERVLISTEND 235
#define RPL_SERVLISTEND_MSG "<mask> <type> :End of service listing"

// RPL_LUSERCLIENT
#define RPL_LUSERCLIENT 251
#define RPL_LUSERCLIENT_MSG ":There are <integer> users and <integer> services on <integer> servers"

// RPL_LUSEROP
#define RPL_LUSEROP 252
#define RPL_LUSEROP_MSG "<integer> :operator(s) online"

// RPL_LUSERUNKNOWN
#define RPL_LUSERUNKNOWN 253
#define RPL_LUSERUNKNOWN_MSG "<integer> :unknown connection(s)"

// RPL_LUSERCHANNELS
#define RPL_LUSERCHANNELS 254
#define RPL_LUSERCHANNELS_MSG "<integer> :channels formed"

// RPL_LUSERME
#define RPL_LUSERME 255
#define RPL_LUSERME_MSG ":I have <integer> clients and <integer> servers"

// RPL_ADMINME
#define RPL_ADMINME 256
#define RPL_ADMINME_MSG "<server> :Administrative info"

// RPL_ADMINLOC1
#define RPL_ADMINLOC1 257
#define RPL_ADMINLOC1_MSG ":<admin info>"

// RPL_ADMINLOC2
#define RPL_ADMINLOC2 258
#define RPL_ADMINLOC2_MSG ":<admin info>"

// RPL_ADMINEMAIL
#define RPL_ADMINEMAIL 259
#define RPL_ADMINEMAIL_MSG ":<admin info>"

// RPL_TRYAGAIN
#define RPL_TRYAGAIN 263
#define RPL_TRYAGAIN_MSG "<command> :Please wait a while and try again."
