/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:56:35 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 15:21:27 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int Server::oper(int cc, std::vector<std::string> tokens){
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
	return 0;
}

void Server::changeoper(std::vector<std::string> tokens, int cc)
{
	if (!check_params(tokens, 3)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("OPER"));}
	else if(oper(cc, tokens) == 1)
	{
		if(_clients[cc].admin == true)
		{
			_clients[cc].send_to_user += SERVERNAME" You already are an IRC operator\r\n";
			return;
		}
		_clients[cc].admin = true;
		_clients[cc].send_to_user += irc::cEM(irc::RPL_YOUREOPER());
	}
	else if(oper(cc, tokens) == 2)
		_clients[cc].send_to_user += irc::cEM(irc::ERR_PASSWDMISMATCH());
	else
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NOOPERHOST());
}
