/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:52:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/25 19:22:34 by ccompote         ###   ########.fr       */
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

void Server::sendmsg(std::vector<std::string> tokens, std::string nick) 
{
    for (size_t i = 0; i < _channels.size(); i++) 
	{
        if (_channels[i].name == tokens[1])
		{
			std::cout << ":" + nick + " PRIVMSG " + tokens[1] + " :"+ tokens[2] + "\r\n";
			std::string resp =  ":" + nick + " PRIVMSG " + tokens[1] + " :" + tokens[2] + "\r\n";	
            for (size_t j = 0; j < _channels[i].members.size(); j++)
			{
				for (size_t k = 0; k < _poll_fds.size(); k++)
				{
            	    if (_poll_fds[k].fd == _clients[_channels[i].members[j]].fd
						&& _clients[_channels[i].members[j]].nick != nick)
					{
						_clients[_channels[i].members[j]].send_to_user +=  resp;
						logsend(_poll_fds[k].fd, _clients[_channels[i].members[j]].send_to_user);
						_clients[_channels[i].members[j]].send_to_user = "";
					}
            	}
			}
			return ;
        }
    }
	std::string resp = ":" + nick + " PRIVMSG " + tokens[1] + " :";
	for (int i = 2; tokens[i].size() != 0; i++)
		resp += " " + tokens[i];
	resp += "\r\n";
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == tokens[1])
			_clients[i].send_to_user += resp;
	}
}

int Server::joinchannel(std::vector<std::string> tokens , int cc)
{
	if (tokens.size() == 2)
	{
		std::string channelname;
		if (tokens[1].length() >= 2 && tokens[1][0] == '#')
			channelname = tokens[1].substr(1);
		else if (tokens[1].length() >= 1 && tokens[1][0] != '#')
		{
			channelname = tokens[1];
		}
		else
		{
			std::cout << "Wrong channel name format" << std::endl;
			return 0;
		}
		for (size_t i = 0; i < _channels.size(); i++)
		{
			if (_channels[i].name == channelname)
			{
				for (size_t k = 0; k < _clients[cc]._channels.size(); k++)
				{
					if (_clients[cc]._channels[k] == channelname)
					{
						_clients[cc].send_to_user += SERVERNAME" You are already in this channel\r\n";
						return 1;
					}
				}
				_channels[i].members.push_back(cc);
				_clients[cc]._channels.push_back(_channels[i].name);
				std::string resp = ":" + _clients[cc].nick + " JOIN :" + channelname + "\r\n";		
				_clients[cc].send_to_user += resp;
				return 1;
			}
		}
		Channel newChannel(channelname, "", "itkol");
		newChannel.members.push_back(cc);
		_channels.push_back(newChannel);
		_clients[cc]._channels.push_back(newChannel.name);
		std::string resp = ":" + _clients[cc].nick + " JOIN :" + channelname + "\r\n";	
		_clients[cc].send_to_user += resp;
		return 1;
	}
	else
	{
		_clients[cc].send_to_user += SERVERNAME"Wrong JOIN parameters\r\n";
		return 0;
	}
}

void Server::removefromchannel(std::string channelname, int cc)
{
	for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
	{
		std::cout << "HERE" << std::endl;
		if (_clients[cc]._channels[i] == channelname)
		{
			//remove channel from user
			_clients[cc]._channels.erase(_clients[cc]._channels.begin() + i);
			//remove user from channel
			for (size_t j = 0; j < _channels.size(); j++)
			{
				if (_channels[j].name == channelname)
				{
					for (size_t k = 0; k < _channels[j].members.size(); k++)
					{
						if (_channels[j].members[k] == cc)
						{
							_channels[j].members.erase(_channels[j].members.begin() + k);
							break;
						}
					}
					break ;
				}
			}
			std::string resp = ":" + _clients[cc].nick + " PART :" + channelname + "\r\n";	
			_clients[cc].send_to_user += resp;
			return ;
		}
	}
}

void Server::leavechannel(std::vector<std::string> tokens, int cc)
{
	if (tokens.size() == 2)
	{
		std::string channelname;
		if (tokens[1].length() >= 2 && tokens[1][0] == '#')
			channelname = tokens[1].substr(1);
		else if (tokens[1].length() >= 1 && tokens[1][0] != '#')
			channelname = tokens[1];
		else
		{
			_clients[cc].send_to_user += SERVERNAME"Wrong channel name format\r\n";
			return ;
		}
		_clients[cc].send_to_user += SERVERNAME" You are not in the channel\r\n";
		removefromchannel(channelname, cc);
	}
	else
		_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("PART");
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
	if ((directory = opendir(folderPath.c_str())) != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
		{
            if (strcmp(entry->d_name, "chanops.txt") == 0) 
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
    					        return 3;
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
		return 4;
	return 0;
}

void Server::changeoper(std::vector<std::string> tokens, int cc)
{
	if (tokens[1].empty() || tokens[2].empty())
		_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("OPER");
	else if(oper(tokens) == 1)
	{
		if(_clients[cc].mode.find('o') != std::string::npos)
		{
			_clients[cc].send_to_user += SERVERNAME" You already are an IRC operator\r\n";
		}
		addmode('O', cc);
		_clients[cc].send_to_user += irc::RPL_YOUREOPER();
	}
	else if(oper(tokens) == 0)
		_clients[cc].send_to_user += irc::ERR_NOOPERHOST();
	else if(oper(tokens) == 2)
		_clients[cc].send_to_user += irc::ERR_PASSWDMISMATCH();
	else if(oper(tokens) == 3)
	{
		if(_clients[cc].mode.find('o') != std::string::npos)
		{
			_clients[cc].send_to_user += SERVERNAME" You already are an IRC Channel operator\r\n";
		}
		addmode('o', cc);
		_clients[cc].send_to_user += irc::RPL_YOUREOPER();
	}
	else if(oper(tokens) == 4)
		_clients[cc].send_to_user += irc::ERR_PASSWDMISMATCH();
}

void Server::rmletter(char letter, int cc){
	std::string result;
	bool noletter = true;
    for (std::size_t i = 0; i < _clients[cc].mode.length(); ++i)
	{
        if (_clients[cc].mode[i] != letter)
            result += _clients[cc].mode[i];
        else if (_clients[cc].mode[i] == letter)
			noletter = false;
    }
	if (noletter == true)
	{
        _clients[cc].send_to_user += SERVERNAME" Cannot remove MODE \"";
		_clients[cc].send_to_user += letter;
		_clients[cc].send_to_user += "\" as it was never active\r\n";
	}
    _clients[cc].mode = result;
}

void Server::addmode(char letter, int cc){
	if(_clients[cc].mode.find(letter) == std::string::npos)
	{
		_clients[cc].mode += letter;
	}
}

void Server::addchanmode(char letter, std::string& chanmodes)
{
	if(chanmodes.find(letter) == std::string::npos)
		chanmodes += letter;
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
					|| tokens[2][i] == 'r'
					|| tokens[2][i] == 's'))
					addmode(tokens[2][i], cc);
				if (tokens[2][i] == 'o' || tokens[2][i] == 'O')
					_clients[cc].send_to_user += SERVERNAME" Use OPER cmd to gain priviledges\r\n";
			}
		return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
	}
	else
	{
		for(std::vector<std::string>::size_type i = 0; i < _clients[cc]._channels.size(); i++)
		{
			if (_clients[cc]._channels[i] == tokens[1])
			{
				for(std::vector<std::string>::size_type j = 0; j < _channels.size(); j++)
				{
					if (_clients[cc]._channels[i] == _channels[j].name)
					{
						std::cout << "HERE\n";
						if (!tokens[2].size())
						{

							return(irc::RPL_CHANNELMODEIS(_channels[j].name, _channels[j].mode, _channels[j].modeparams));
						}
						std::cout << "HERE2\n";
						if(_clients[cc].mode.find("o") != std::string::npos
						|| _clients[cc].mode.find("O") != std::string::npos)
						{
							for (int k = 1; tokens[2][k]; k++)
							{
								if (   tokens[2][i] == 'i'
									|| tokens[2][i] == 't'
									|| tokens[2][i] == 'k'
									|| tokens[2][i] == 'o'
									|| tokens[2][i] == 'l')
									addchanmode(tokens[2][i], _channels[j].mode);
								return ("Added mode to channel\r\n");
							}
						}
						else
							return(irc::ERR_NOPRIVILEGES());
					}
				}
			}
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
		if (tokens[3].empty() == false && tokens[4].empty() == false)
		{
			_clients[cc].realname = tokens[4];
			_clients[cc].send_to_user += SERVERNAME" REALNAME has been set to ";
			_clients[cc].send_to_user += tokens[4].c_str();
			_clients[cc].send_to_user += "\r\n";
		}
		else
			_clients[cc].realname = "";
	}
	else if (user == true)
	   	_clients[cc].send_to_user += SERVERNAME" USER has already been taken\r\n"SERVERNAME" Please chooes a different one\r\n";
	else
		_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("USER");
}

void Server::nick(std::vector<std::string> tokens, int cc, int i)
{
	(void)i;
	bool nickinuse = false;
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == tokens[1])
			nickinuse = true;
	}
	if (tokens[1].empty() == true)
	   	_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("NICK");
	else if (tokens[1].size() < 1)
	    _clients[cc].send_to_user += SERVERNAME" NICK too short\r\n";
	else if (tokens.size() > 1 && nickinuse == false)
	{
	    _clients[cc].nick = tokens[1];
	    _clients[cc].send_to_user += SERVERNAME" NICK has been set to ";
	    _clients[cc].send_to_user += tokens[1].c_str();
		_clients[cc].send_to_user += "\r\n";
	}
	else if (nickinuse == true)
	   	_clients[cc].send_to_user += SERVERNAME" NICK has already been taken\r\n"SERVERNAME" Please chooes a different one\r\n";
}

void Server::quit(std::vector<std::string> tokens, int i, int cc)
{
	if (tokens[1].empty() == false)
	    logsend(_poll_fds[i].fd, tokens[1].c_str());
	for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
		removefromchannel(_clients[cc]._channels[i], cc);
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
	_clients[cc].send_to_user += "PONG " + _clients[cc].nick + " " + tokens[2] + "\r\n";
}