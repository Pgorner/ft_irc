/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:46:57 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 14:38:24 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

namespace LogDetail {
    struct LogStream {
        std::ofstream logFile;
        bool isOpen;
        int logNumber;

        LogStream() : isOpen(false), logNumber(0) {
            std::string folderName = "logs";

            DIR *dir = opendir(folderName.c_str());
            struct dirent *ent;
            if (dir != NULL) {
                while ((ent = readdir(dir)) != NULL) {
                    std::string fileName = ent->d_name;
                    if (fileName.substr(0, 4) == "log_" && fileName.substr(fileName.size() - 4) == ".txt") {
                        int fileNumber = atoi(fileName.substr(4, fileName.size() - 8).c_str());
                        if (fileNumber > logNumber) {
                            logNumber = fileNumber;
                        }
                    }
                }
                closedir(dir);
            }

            std::ostringstream oss;
            oss << folderName << "/log_" << logNumber << ".txt";
            std::string fileName = oss.str();
            if (logNumber > 0) {
                logFile.open(fileName.c_str(), std::ios::app);
                isOpen = logFile.is_open();
            }
        }

        ~LogStream() {
            if (isOpen) {
                logFile.close();
            }
        }

        // Function to get the current time as a formatted string
        std::string getCurrentTime() {
            std::time_t now = std::time(0);
            char timeStr[100];
            std::strftime(timeStr, sizeof(timeStr), "[%Y-%m-%d %H:%M:%S]", std::localtime(&now));
            return std::string(timeStr);
        }

        template <typename T>
        LogStream &operator<<(const T &data) {
            if (isOpen) {
                logFile << getCurrentTime() << " " << data << "\n";
            }
            return *this;
        }
    };
}

// Define LOG to redirect output to the next available log file in the "logs" folder
#define LOG LogDetail::LogStream()

#endif // LOG_HPP
