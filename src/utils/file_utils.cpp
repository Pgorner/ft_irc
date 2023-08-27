/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:51:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 21:06:32 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool Server::fileExists(const std::string& fileName) 
{
    FILE* file = fopen(fileName.c_str(), "r");
    if (file)
	{
        fclose(file);
        return true;
    }
    return false;
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
