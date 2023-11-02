/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:17:04 by pgorner           #+#    #+#             */
/*   Updated: 2023/11/02 16:51:38 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP_
#define IRC_HPP_

#define FALSE 0
#define TRUE 1
#define INDETERMINATE 2
#define DEBUG 1 //set to 0 for debugging mode (NO ANIMATIONS)
#define SERVERNAME "IRCSERV"
#define POLLTIME 500 


#include <string>
#include <vector>
#include <csignal>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <poll.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ------ own libs -------
#include "server.hpp"
#include "replies.hpp"
#include "typography.hpp"
#include "log.hpp"


int err(std::string msg);
int welcome(int argc, char **argv);
void clear(int i);
void write_irc(void);
std::string ctstr(void);
void log_creation(void);
void log(std::string log);
void write_nice(const char color[6], std::string str, bool nl);
bool isValidPort(const char* port);

#endif
