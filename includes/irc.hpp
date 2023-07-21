/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:17:04 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/21 19:20:23 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP_
#define IRC_HPP_
#define WRITESPEED 3000
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


// ------ c++ libs ------
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <memory>


// ------- c libs -------
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>

// ------ own libs ------
#include "server.hpp"

// error.cpp -------------------------------------
void err(std::string msg);
int welcome(int argc, char **argv);
// utils.cpp -------------------------------------
void SetTerminalEcho(bool enable);
void SetTerminalNonBlocking(bool nonBlocking);

#endif