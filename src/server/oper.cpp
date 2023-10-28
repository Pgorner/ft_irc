/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:56:35 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/28 16:54:12 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int Server::oper(std::vector<std::string> tokens, int cc){
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
    					    if (usertkn[1] == tokens[1] &&  usertkn[2] == tokens[2] && usertkn[1] == _clients[cc].user)
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
    					    if (usertkn[1] == tokens[1] &&  usertkn[2] == tokens[2] && usertkn[1] == _clients[cc].user)
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
	std::cout << CYAN << oper(tokens, cc) << std::endl;
	if (!check_params(tokens, 3)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("OPER"));}
	else if(oper(tokens, cc) == 1)
	{
		if(string_contains(_clients[cc].mode, 'O'))
		{
			_clients[cc].send_to_user += SERVERNAME" You already are an IRC operator\r\n";
			return;
		}
		addmode('O', cc);
		_clients[cc].send_to_user += irc::cEM(irc::RPL_YOUREOPER());
	}
	else if(oper(tokens, cc) == 2)
		_clients[cc].send_to_user += irc::cEM(irc::ERR_PASSWDMISMATCH());
	else if(oper(tokens, cc) == 3)
	{
		if(string_contains(_clients[cc].mode, 'o'))
		{
			_clients[cc].send_to_user += SERVERNAME" You already are an IRC Channel operator\r\n";
			return;
		}
		addmode('o', cc);
		_clients[cc].send_to_user += irc::cEM(irc::RPL_YOUREOPER());
	}
	else if(oper(tokens, cc) == 4)
		_clients[cc].send_to_user += irc::cEM(irc::ERR_PASSWDMISMATCH());
	else if(oper(tokens, cc) == 0)
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NOOPERHOST());
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

int Server::rmchanletter(char letter, int cc, int channel){
	std::string result;
	bool noletter = true;
    for (std::size_t i = 0; i < _channels[channel].mode.length(); ++i)
	{
        if ( _channels[channel].mode[i] != letter)
            result +=  _channels[channel].mode[i];
        else if ( _channels[channel].mode[i] == letter)
			noletter = false;
    }
	if (noletter == true)
	{
        _clients[cc].send_to_user += SERVERNAME" Cannot remove MODE \"";
		_clients[cc].send_to_user += letter;
		_clients[cc].send_to_user += "\" as it was never active\r\n";
		return -1;
	}
    _channels[channel].mode = result;
	return 1;
}