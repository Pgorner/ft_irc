/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:07:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 20:57:50 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::ping(std::vector<std::string> tokens,int cc)
{
	_clients[cc].send_to_user += "PONG " + _clients[cc].nick + " " + tokens[2] + "\r\n";
}

void    clear(int i)
{
    for (int k = 0; k <= i; k++)
        std::cout << "\033[A\033[2K";
}

void    write_nice(const char color[6], std::string str, bool nl)
{
    setlocale(LC_ALL, "");
    if (nl == true)
        str += "\n";
    unsigned long k = 0;
    while (k < str.size()) 
    {
        std::cout << color << str[k++] << RESET << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    }
}
void    write_irc(void){
    unsigned long k = 0;
	std::string str = IRC;
    while (k < str.size()) 
    {
        std::cout << str[k++] << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));
    }
}

void log(std::string log)
{
    LOG << log;
}

void Server::logsend(int fd, const std::string& msg, int cc)
{
    LOG << "SERVER SENT: ";
    LOG << msg;
    std::cout << YELLOW << "SERVER SENT:\n" << msg << std::endl;
    if (cc != -1)
        std::cout << YELLOW << "TO:\n" << _clients[cc].nick << std::endl;
    bool hasNewline = false;
    for (size_t i = 0; i < msg.length(); ++i) {
        if (msg[i] == '\n') {
            hasNewline = true;
            break;
        }
    }
    (void)hasNewline;
    send(fd, msg.c_str(), msg.size(), 0);
}

bool Server::contains(const std::vector<std::string>& tokens, std::string search) {
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
        if (*it == search) {
            return true;
        }
    }
    return false;
}

void Server::change_running(int signal) {
    (void)signal;
    endwin();
    server_ptr->proper_exit();
    exit(0);
}

bool Server::isAllDigits(const std::string& str)
{
    for (std::size_t i = 0; i < str.length(); ++i)
        if (!isdigit(str[i]))
            return false;
    return true;
}

bool validateUser(const std::string& filePath, const std::string& username, const std::string& password)
{
    std::ifstream file(filePath.c_str());
    std::string line;

    while (std::getline(file, line)) {
        std::string tokens[3];

        std::istringstream iss(line);
        for (int i = 1; i <= 2 && std::getline(iss, tokens[i], ' '); ++i);
        if (tokens[1] == username && tokens[2] == password)
            return true;
    }

    return false;
}