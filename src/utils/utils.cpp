/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:07:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/25 17:43:12 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void    clear(int i)
{
    for (int k = 0; k <= i; k++)
        std::cout << "\033[A\033[2K";
}

void    goodbye(void)
{
    if (DEBUG){
        clear(100);
        write_nice(YELLOW, GOODBYE, false);
    }
}
void    write_nice(const char color[6], std::string str, bool nl)
{
    setlocale(LC_ALL, "");
    log(str);
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

void Server::change_running(int signal)
{
    if (signal == SIGINT || signal == SIGQUIT){
        running = false;
        proper_exit();
        goodbye();
        exit(1);
    }
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