/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:55:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/28 19:25:30 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::kick(std::vector<std::string> tokens , int cc)
{
	if (!check_params(tokens, 3) || !check_tokensize(tokens[1], 2) || tokens[1][0] != '#')
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("KICK"));
		return ;
	}
	std::string channelname = tokens[1];
	if (string_contains(_clients[cc].mode, 'O')|| string_contains(_clients[cc].mode, 'o'))
	{
		for (size_t i = 0; i < _channels.size(); i++)
		{
			if (_channels[i].name == channelname)
			{
				int target = find_user(tokens[2]);
				if (target == -1) {_clients[cc].send_to_user += SERVERNAME" User not found on server\r\n"; return ;}
				if (!find_user_inchan(i, target)){_clients[cc].send_to_user += SERVERNAME" User not found in channel\r\n"; return ;}
				if (cc == target) {_clients[cc].send_to_user += SERVERNAME" You cannot kick yourself\r\n"; return ;}
				std::string msg = " :";
				if (tokens[3].size() != 0)
					msg += tokens[3];
				removefromchannel(channelname, target, "KICK " + channelname + " " + tokens[2] + msg + "\r\n");
				_clients[cc].send_to_user += SERVERNAME" User kicked\r\n";
				return ;
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