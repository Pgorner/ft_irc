/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:17:04 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/03 17:52:04 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP_
#define IRC_HPP_

#define DEBUG 0 //set to 0 for debugging mode (NO ANIMATIONS)

static int running = true;

// ------ c++ libs -------
#include <string>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

// ------- c libs --------
#include <poll.h>
#include <fcntl.h> 
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <ncurses.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ------ own libs -------
#include "server.hpp"
#include "errcode.hpp"
#include "replies.hpp"
#include "typography.hpp"
#include "log.hpp"

// error.cpp -------------------------------------
int err(std::string msg);
int welcome(int argc, char **argv);
// utils.cpp -------------------------------------
void	clear(int i);
void	write_irc(void);
std::string ctstr(void);
void	log_creation(void);
void	log(std::string log);
void    write_nice(const char color[6], std::string str, bool nl);

#endif