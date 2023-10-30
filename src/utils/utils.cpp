/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:07:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 15:33:29 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/irc.hpp"

void clear(int i) {
    for (int k = 0; k <= i; k++)
        std::cout << "\033[A\033[2K";
}

void Server::goodbye(void) {
    if (DEBUG) {
        clear(100);
        clear(100);
        write_nice(YELLOW, GOODBYE, false);
    }
    system("leaks ircserv");
}

void write_nice(const char color[6], std::string str, bool nl) {
    setlocale(LC_ALL, "");
    if (nl == true)
        str += "\n";
    unsigned long k = 0;
    while (k < str.size()) {
        std::cout << color << str[k++] << RESET << std::flush;
        // Sleep functionality removed for C++98
    }
}

void write_irc(void) {
    unsigned long k = 0;
    std::string str = IRC;
    while (k < str.size()) {
        std::cout << str[k++] << std::flush;
        // Sleep functionality removed for C++98
    }
}

void log(std::string log) {
    LOG << log;
}

void Server::logsend(int fd, const std::string& msg, int cc) {
    LOG << "SERVER SENT: ";
    LOG << msg;
    std::cout << YELLOW << "SERVER SENT:\n" << msg << std::endl;
    if (cc != -1)
        std::cout << YELLOW << "TO:\n" << _clients[cc].nick << std::endl;
    send(fd, msg.c_str(), msg.size(), 0);
}

bool Server::check_params(std::vector<std::string>& tokens, size_t count)
{
	if (tokens.size() < count)
		return(false);
	return (true);
}

bool Server::check_tokensize(std::string& token, size_t size)
{
	if (token.size() < size)
		return(false);
	return(true);
}

bool Server::string_contains(const std::string& token, char search)
{
    if(token.find(search) != std::string::npos)
        return(true);
    return(false);
}

bool Server::token_contains(const std::vector<std::string>& tokens, std::string search) {
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
        if (*it == search)
            return true;
    }
    return false;
}

void Server::change_running(int signal) {
    (void)signal;
    exit(0);
}

void log_creation(void) {
    std::ofstream logFile;
    bool isOpen;
    int logNumber = 0;

    std::string folderName = "logs";
    struct stat folderBuffer;
    // Create the "logs" folder if it doesn't exist
    if (stat(folderName.c_str(), &folderBuffer) != 0)
        mkdir(folderName.c_str(), 0777);
    // Find the latest log file number
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(folderName.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            if (fileName.rfind("log_", 0) == 0) { // Check if the file name starts with "log_"
                int fileNumber = atoi(fileName.substr(4, fileName.find(".txt") - 4).c_str());
                if (fileNumber > logNumber)
                    logNumber = fileNumber;
            }
        }
        closedir(dir);
    }
    logNumber++;
    std::ostringstream oss;
    oss << folderName << "/log_" << logNumber << ".txt";
    std::string fileName = oss.str();
    logFile.open(fileName.c_str(), std::ios_base::app);
    isOpen = logFile.is_open();
    if (isOpen)
        logFile.close();
    LOG << LOGFILE;
}

bool Server::isAllDigits(const std::string& str) {
    for (std::size_t i = 0; i < str.length(); ++i)
        if (!isdigit(str[i]))
            return false;
    return true;
}

int Server::sig_handlerserv(void) {
    signal(SIGINT, change_running);
    signal(SIGQUIT, change_running);
    return log("sig_handler started"), 0;
}

void Server::checkPwd(std::vector<std::string>& tokens, int i, int cc) {
    if(!check_params(tokens, 2)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("NICK")); return;};
    if ((tokens.empty() || tokens[0].compare(0, 5, "PASS") != 0))
        logsend(_poll_fds[i].fd, SERVERNAME" : WRONG PASSWORD\r\n", cc);
    else if (tokens[1] == _pwd) 
    {
        _clients[cc].passwordAccepted = TRUE;
        _clients[cc].send_to_user += SERVERNAME" Your PASSWORD is correct\r\n";
    }
    else
        logsend(_poll_fds[i].fd, irc::ERR_PASSWDMISMATCH(), cc);
}

void Server::cap(int fd, const std::vector<std::string>& tokens, bool& cap, int cc) {
    if (token_contains(tokens, "CAP") == true && token_contains(tokens, "LS") == true)
        logsend(fd, "CAP * LS :\n", cc);
    else if (token_contains(tokens, "CAP") == true && token_contains(tokens, "REQ") == true){
        std::string req = "CAP * ACK :";
        if (token_contains(tokens, "multi-prefix"))
            req += "multi-prefix";
        if (token_contains(tokens, "multiple-channel-joins"))
            req += "multiple-channel-joins";
        logsend(fd, req.c_str(), cc);
    }
    else if (token_contains(tokens, "CAP") == true && token_contains(tokens, "END") == true)
        cap = true;
}
