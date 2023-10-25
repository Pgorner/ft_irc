/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:55:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 18:25:42 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::kick(std::vector<std::string> tokens , int cc)
{
	std::string channelname;
	if (tokens[1].length() >= 2 && tokens[1][0] == '#' && !tokens[1].empty() && !tokens[2].empty())
		channelname = tokens[1];
	else
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("KICK"));
		std::cout << "Wrong channel name format // Missing params" << std::endl;
		return ;
	}
	if (_clients[cc].mode.find('O') != std::string::npos || _clients[cc].mode.find('o') != std::string::npos)
	{
		for (size_t i = 0; i < _channels.size(); i++)
		{
			if (_channels[i].name == channelname)
			{
				int target = find_user(tokens[2]);
				if (target != -1)
				{
					std::string msg = " :";
					if (tokens[3].size() != 0)
						msg += tokens[3];
					removefromchannel(channelname, target, "KICK " + channelname + " " + tokens[2] + msg + "\r\n");
					_clients[cc].send_to_user += SERVERNAME" User kicked\r\n";
					return ;
				}
				else
				{
					_clients[cc].send_to_user += SERVERNAME" User not found\r\n";
					return ;
				}
			}
		}
		_clients[cc].send_to_user += SERVERNAME" Channel doesn't exist\r\n";
	}
	else
		_clients[cc].send_to_user += irc::cEM(irc::ERR_CHANOPRIVSNEEDED(tokens[1]));
}

void Server::removefromchannel(std::string channelname, int cc, std::string msg)
{
	int track = 0;
	if (msg.size() != 0)
		broadcastinchannel(channelname, msg);
	std::vector<std::string>& channels = _clients[cc]._channels;
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end();)
	{
	    if (*it == channelname)
		{
	        it = channels.erase(it);
			track += 1;
		}
		else
	        ++it;
	}
	
	for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
	    if (it->name == channelname)
		{
	        std::vector<int>& members = it->members;
	        for (std::vector<int>::iterator iter = members.begin(); iter != members.end();)
			{
	            if (*iter == cc)
				{
	                iter = members.erase(iter);
					track += 1;
	            }
				else
	                ++iter;
	        }
	        break;
		}
	}
	if (track != 2)
		_clients[cc].send_to_user += SERVERNAME" User is not found in the channel\r\n";
}	