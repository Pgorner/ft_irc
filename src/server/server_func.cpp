/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:52:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/21 17:49:41 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/irc.hpp"


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

bool fileExists(const std::string& fileName) 
{
    FILE* file = fopen(fileName.c_str(), "r");
    if (file)
	{
        fclose(file);
        return true;
    }
    return false;
}

void Server::sendmsg(std::vector<std::string> tokens) 
{
    for (size_t i = 0; i < _channels.size(); i++) 
	{
        if (_channels[i].name == tokens[1]) 
		{
            for (size_t j = 0; j < _channels[i].members.size(); j++) 
			{
                std::cout << tokens[2] << " sent to " <<  (_channels[i].members)[j].nick << " with fd " << (_channels[i].members)[j].fd << std::endl;
                logsend((_channels[i].members)[j].fd, tokens[2]);
            }
        }
    }
}

int Server::joinchannel(std::vector<std::string> tokens , int cc)
{
	if (tokens.size() == 2)
	{
		std::string channelname;
		if (tokens[1].length() >= 2 && tokens[1][0] == '#')
			channelname = tokens[1].substr(1);
		else
		{
			std::cout << "Wrong channel name format" << std::endl;
			return 0;
		}
		for (size_t i = 0; i < _channels.size(); i++)
		{
			if (_channels[i].name == channelname)
			{
				_channels[i].members.push_back(_clients[cc]);
				// for (size_t j = 0; j < _channels[i].members.size(); j++) 
				// {
				// 	std::cout << "name is " << _channels[i].members.name << " fd is " << _channels[i].members.name << " cc is " << _clients[cc].fd << std::endl;
				// }
				_clients[cc]._channels.push_back(_channels[i].name);
				std::string resp = ":" + _clients[cc].nick + " JOIN :" + channelname + "\r\n";
				logsend(_clients[cc].fd, resp);		
				return 1;
			}
		}
		Channel newChannel;
		newChannel.name = channelname;
		newChannel.members.push_back(_clients[cc]);
		// for (size_t j = 0; j < _channels[i].members.size(); j++) 
		// 		{
		// 			std::cout << "name is " << newChannel.members.name << " fd is " << newChannel.members.name << " cc is " << _clients[cc].fd << std::endl;
		// 		}
		_channels.push_back(newChannel);
		_clients[cc]._channels.push_back(newChannel.name);
		std::string resp = ":" + _clients[cc].nick + " JOIN :" + channelname + "\r\n";
		logsend(_clients[cc].fd, resp);	
		return 1;
	}
	else
	{
		std::cout << "Wrong JOIN parameters" << std::endl;
		return 0;
	}
}

int Server::oper(std::vector<std::string> tokens){
	std::string folderPath = "src/documentation";
	DIR* directory;
    struct dirent* entry;
	int keeptrack = 0;
    if ((directory = opendir(folderPath.c_str())) != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
		{
            if (strcmp(entry->d_name, "admins.txt") == 0) 
				{
                	std::string filePath = folderPath + "/" + entry->d_name;
                	if (fileExists(filePath))
					{
						std::ifstream file(filePath.c_str());
						std::string line;
    					while (std::getline(file, line))
						{
    					    std::string usertkn[3];
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
	else
	{
        std::cerr << SERVERNAME" Error opening directory!" << std::endl;
        return 0;
	}
	if (keeptrack == 1)
		return 2;
	else
		return 0;
}

void Server::rmletter(char letter, int cc){
	std::string result;
    for (std::size_t i = 0; i < _clients[cc].mode.length(); ++i)
	{
        if (_clients[cc].mode[i] != letter)
            result += _clients[cc].mode[i];
    }
    _clients[cc].mode = result;
}

void Server::addmode(char letter, int cc){
	if(_clients[cc].mode.find(letter) == std::string::npos)
	{
		_clients[cc].mode += letter;
	}
}

const char* Server::mode(int cc, std::vector<std::string> tokens){
	if (tokens[1] == _clients[cc].nick)
	{
		if (tokens[2][0] == '-')
		{
			for (int i = 1; tokens[2][i]; i++)
				rmletter(tokens[2][i], cc);	
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2][0] == '+')
		{
			for (int i = 1; tokens[2][i]; i++)
			{
				if ((tokens[2][i] != 'o' || tokens[2][i] != 'O' || tokens[2][i] != 'a') &&
					(tokens[2][i] == 'a'
					|| tokens[2][i] == 'i'
					|| tokens[2][i] == 'w'
					|| tokens[2][i] == 'o'
					|| tokens[2][i] == 'r'
					|| tokens[2][i] == 's'))
					addmode(tokens[2][i], cc);
			}
		return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
	}
	return (irc::ERR_USERSDONTMATCH());
}

void Server::user(std::vector<std::string> tokens, int cc, int i)
{
	(void)i;
	bool user = false;
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].user == tokens[1])
			user = true;
	}
	if (tokens[1].empty() == true)
	   	_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("USER");
	else if (tokens[1].size() < 1)
	    _clients[cc].send_to_user += SERVERNAME" USER too short\r\n";
	else if (tokens.size() > 1 && user == false)
	{
		_clients[cc].user = tokens[1];
	    _clients[cc].send_to_user += SERVERNAME" USER has been set to ";
	    _clients[cc].send_to_user += tokens[1].c_str();
		_clients[cc].send_to_user += "\r\n";
		if (tokens[2].empty() == false)
		{
			if (tokens[2] == "8")
				addmode('i', cc);
			else if (tokens[2] == "2")
				addmode('w', cc);
			if (tokens[2] == "8" || tokens[2] == "2"){
				_clients[cc].send_to_user += irc::RPL_UMODEIS(_clients[cc].mode);
			}
		}
		if (tokens[4].empty() == false)
		{
			_clients[cc].realname = tokens[4];
			_clients[cc].send_to_user += SERVERNAME" REALNAME has been set to ";
			_clients[cc].send_to_user += tokens[4].c_str();
			_clients[cc].send_to_user += "\r\n";
		}
	}
	else if (user == true)
	   	_clients[cc].send_to_user += SERVERNAME" USER has already been taken\r\n";
	else
		_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("USER");
}

void Server::nick(std::vector<std::string> tokens, int cc, int i)
{
	(void)i;
	bool nick = false;
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == tokens[1])
			nick = true;
	}
	if (tokens[1].empty() == true)
	   	_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("NICK");
	else if (tokens[1].size() < 1)
	    _clients[cc].send_to_user += SERVERNAME" NICK too short\r\n";
	else if (tokens.size() > 1 && nick == false)
	{
	    _clients[cc].nick = tokens[1];
	    _clients[cc].send_to_user += SERVERNAME" NICK has been set to ";
	    _clients[cc].send_to_user += tokens[1].c_str();
		_clients[cc].send_to_user += "\r\n";
	}
	else if (nick == false)
	   	_clients[cc].send_to_user += SERVERNAME" NICK has already been taken\r\n";
}

void Server::quit(std::vector<std::string> tokens, int i, int cc)
{
	if (tokens[1].empty() == false)
	    logsend(_poll_fds[i].fd, tokens[1].c_str());
	close(_poll_fds[i].fd);
    _poll_fds.erase(_poll_fds.begin() + i);
	write_nice(RED, "Client: ", false);
	write_nice(RED, _clients[cc].realname, false);
	write_nice(RED, " disconnected", true);
	_clients.erase(_clients.begin() + cc);
	close(_poll_fds[i].fd);
}

void Server::ping(std::vector<std::string> tokens,int cc)
{
	_clients[cc].send_to_user += "PONG " + _clients[cc].nick + " " + tokens[2];
}