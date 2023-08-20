/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:52:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/20 17:08:30 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/irc.hpp"


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

std::string Server::rmletter(char letter, std::string mode){
	std::string result;
    for (std::size_t i = 0; i < mode.length(); ++i) {
        if (mode[i] != letter)
            result += mode[i];
    }
    return result;
}

std::string Server::addmode(char letter, std::string mode){
	if(mode.find(letter) != std::string::npos)
		return (mode += letter);
	else
		return mode;
}

const char* Server::mode(int cc, std::vector<std::string> tokens){
	if (tokens[1] == _clients[cc].nick){
		if (tokens[2] == "+o" || tokens[2] == "+o" || tokens[2] == "a")
			return "no";
		else if (tokens[2] == "-o" || tokens[2] == "-O"){
			_clients[cc].mode = rmletter('o', _clients[cc].mode);
			_clients[cc].mode = rmletter('O', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "i"){
			_clients[cc].mode = addmode('i', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "-i"){
			_clients[cc].mode = rmletter('i', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "w"){
			_clients[cc].mode = addmode('w', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "-w"){
			_clients[cc].mode = rmletter('i', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "r"){
			_clients[cc].mode = addmode('r', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "-r"){
			_clients[cc].mode = rmletter('r', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "s")
			_clients[cc].mode = addmode('s', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2] == "-s"){
			_clients[cc].mode = rmletter('s', _clients[cc].mode);
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
	return (irc::ERR_USERSDONTMATCH());
}

void Server::user(std::vector<std::string> tokens, int cc, int i){
	bool user = false;
	for(size_t i = 0; i < _clients.size(); i++){
		if (_clients[i].user == tokens[1])
			user = true;
	}
	if (tokens[1].empty() == true)
	   	logsend(_poll_fds[i].fd, irc::ERR_NEEDMOREPARAMS("USER"), true);
	else if (tokens[1].size() < 1)
	    logsend(_poll_fds[i].fd, "USER too short", true);
	else if (tokens.size() > 1 && user == false){
		_clients[cc].user = tokens[1];
	    logsend(_poll_fds[i].fd, "USER has been set to", true);
	    logsend(_poll_fds[i].fd, tokens[1].c_str(), true);
		if (tokens[2].empty() == false){
			if (tokens[2] == "8")
				_clients[cc].mode = addmode('i', _clients[cc].mode);
			else if (tokens[2] == "2")
				_clients[cc].mode = addmode('w', _clients[cc].mode);
			if (tokens[2] == "8" || tokens[2] == "2"){
				logsend(_poll_fds[i].fd, "MODE has been set to", true);
				logsend(_poll_fds[i].fd, tokens[2].c_str(), true);
			}
		}
		if (tokens[4].empty() == false){
			_clients[cc].realname = tokens[4];
			logsend(_poll_fds[i].fd, "REALNAME has been set to", true);
			logsend(_poll_fds[i].fd, tokens[4].c_str(), true);
		}
		}
	else if (user == true)
	   	logsend(_poll_fds[i].fd, "USER has already been taken", true);
	else
		logsend(_poll_fds[i].fd, irc::ERR_NEEDMOREPARAMS("USER"), true);
}

void Server::nick(std::vector<std::string> tokens, int cc, int i){
	bool nick = false;
	for(size_t i = 0; i < _clients.size(); i++){
		if (_clients[i].nick == tokens[1])
			nick = true;}
	if (tokens[1].empty() == true)
	   	logsend(_poll_fds[i].fd, irc::ERR_NEEDMOREPARAMS("NICK"), true);
	else if (tokens[1].size() < 1)
	    logsend(_poll_fds[i].fd, "NICK too short", true);
	else if (tokens.size() > 1 && nick == false){
	    _clients[cc].nick = tokens[1];
	    logsend(_poll_fds[i].fd, "NICK has been set to", true);
	    logsend(_poll_fds[i].fd, tokens[1].c_str(), true);
	}
	else if (nick == false)
	   	logsend(_poll_fds[i].fd, "NICK has already been taken", true);
}

void Server::quit(std::vector<std::string> tokens, int i){
	if (tokens[1].empty() == false)
	    logsend(_poll_fds[i].fd, tokens[1].c_str(), true);
	close(_poll_fds[i].fd);
}