/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:07:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/23 15:12:17 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"


void    clear(int i)
{
    for (int k = 0; k <= i; k++)
        std::cout << "\033[A\033[2K";
}

void    Server::goodbye(void)
{
    if (PIGEON){
        clear(100);
        for (int i = 0; i <= 10; i++){
            if (i % 2 == 0)
                std::cout << PIGEON1 << std::flush;
            else
                std::cout << PIGEON2 << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            clear(21);
        }
    }
    else if (DEBUG){
        clear(100);
        clear(100);
        write_nice(YELLOW, GOODBYE, false);
    }
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

void Server::logsend(int fd, const std::string& msg)
{
    LOG << "SERVER SENT: ";
    LOG << msg;
    std::cout << YELLOW << "SERVER SENT:\n" << msg << std::endl;
    bool hasNewline = false;
    for (size_t i = 0; i < msg.length(); ++i) {
        if (msg[i] == '\n') {
            hasNewline = true;
            break;
        }
    }
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

void log_creation(void){
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
        if ((dir = opendir(folderName.c_str())) != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                std::string fileName = ent->d_name;
                if (fileName.rfind("log_", 0) == 0) { // Check if the file name starts with "log_"
                    int fileNumber = std::stoi(fileName.substr(4, fileName.find(".txt") - 4));
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