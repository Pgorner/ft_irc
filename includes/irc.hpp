/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:17:04 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 15:39:13 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP_
#define IRC_HPP_

// ------ c++ libs -------
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <iostream>


// ------- c libs --------
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ------ own libs -------
#include "server.hpp"
#include "typography.hpp"

// error.cpp -------------------------------------
int err(std::string msg);
int welcome(int argc, char **argv);
// utils.cpp -------------------------------------
void SetTerminalEcho(bool enable);
void SetTerminalNonBlocking(bool nonBlocking);
void    clear(int i);
void    write_nice(const char color[6], std::string str);
void    write_irc(void);
#endif