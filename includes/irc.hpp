/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:17:04 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/24 13:48:24 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP_
#define IRC_HPP_

static int running = true;

// ------ c++ libs -------
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

// ------- c libs --------
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ------ own libs -------
#include "server.hpp"
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
void	change_running(int signal);
void	write_nice(const char color[6], std::string str);

#endif