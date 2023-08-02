/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:52:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/02 20:36:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/server.hpp"


bool validateUser(const std::string& filePath, const std::string& username, const std::string& password) {
    std::ifstream file(filePath.c_str());
    std::string line;

    while (std::getline(file, line)) {
        std::string tokens[3]; // We need 3 tokens (0 for empty, 1 for username, 2 for password)

        std::istringstream iss(line);
        for (int i = 1; i <= 2 && std::getline(iss, tokens[i], ' '); ++i);

        if (tokens[1] == username && tokens[2] == password) {
            return true;
        }
    }

    return false;
}

bool fileExists(const std::string& fileName) {
    FILE* file = fopen(fileName.c_str(), "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

int Server::oper(std::vector<std::string> tokens){
	std::string folderPath = "src/documentation";
	DIR* directory;
    struct dirent* entry;
	int keeptrack = 0;
    if ((directory = opendir(folderPath.c_str())) != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            if (strcmp(entry->d_name, "admins.txt") == 0) 
				{
                	std::string filePath = folderPath + "/" + entry->d_name;
                	if (fileExists(filePath))
					{
						std::ifstream file(filePath.c_str());
						std::string line;
    					while (std::getline(file, line)) {
    					    std::string usertkn[3]; // We need 3 tokens (0 for empty, 1 for username, 2 for password)
    					    std::istringstream iss(line);
    					    for (int i = 1; i <= 2 && std::getline(iss, usertkn[i], ' '); ++i);
    					    if (usertkn[1] == tokens[1] &&  usertkn[2] == tokens[2])
    					        return 1;
							else if (usertkn[1] == tokens[1] &&  usertkn[2] != tokens[2])
								keeptrack = 1;
    					}
                	}
            }
        }
        closedir(directory);
    } 
	else{
        std::cerr << "Error opening directory!" << std::endl;
        return 0;}
	if (keeptrack == 1)
		return 2;
	else
		return 0;
}

const char* Server::mode(int cc, std::vector<std::string> tokens){
	if (tokens[1] == _clients[cc].nick){
		if (tokens[2] == "+o" || tokens[2] == "+o" || tokens[2] == "a")
			return "no";
		else if (tokens[2] == "-o" || tokens[2] == "-o"){
			return("/");
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "i"){
			_clients[cc].mode = "i";
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "-i"){
			if (_clients[cc].mode == "i")
				_clients[cc].mode = "/";
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "w"){
			return ("w");
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "-w"){
			if (_clients[cc].mode == "w")
				_clients[cc].mode = "/";
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "r"){
			_clients[cc].mode = "r";
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "-r"){
			if (_clients[cc].mode == "r")
				_clients[cc].mode = "/";
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "s")
			_clients[cc].mode = "s";
			return (RPL_UMODEIS_MSG);
		}
		else if (tokens[2] == "-s"){
			if (_clients[cc].mode == "s")
				_clients[cc].mode = "/";
			return (RPL_UMODEIS_MSG);
	}
	std::cout << tokens[1] << "!=" << _clients[cc].nick;
	return (ERR_USERSDONTMATCH_MSG);
}