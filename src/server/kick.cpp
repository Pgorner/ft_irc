/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:55:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 15:43:32 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool Server::client_oper(int cc, int channel)
{
	for(size_t i = 0; i < _channels[channel].opers.size(); i++)
	{
		if (cc == _channels[channel].opers[i])
			return true;
	}
	return false;
}
void Server::kick(std::vector<std::string> tokens , int cc)
{
	if (!check_params(tokens, 3) || !check_tokensize(tokens[1], 2) || tokens[1][0] != '#')
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("KICK"));
		return ;
	}
	std::string channelname = tokens[1];
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].name == channelname)
		{
			if (!client_oper(cc, i)){_clients[cc].send_to_user += irc::cEM(irc::ERR_CHANOPRIVSNEEDED(tokens[1])); return;}
			int target = find_user(tokens[2]);
			if (target == -1) {_clients[cc].send_to_user += SERVERNAME" User not found on server\r\n"; return ;}
			if (!find_user_inchan(i, target)){_clients[cc].send_to_user += SERVERNAME" User not found in channel\r\n"; return ;}
			if (cc == target) {_clients[cc].send_to_user += SERVERNAME" You cannot kick yourself\r\n"; return ;}
			std::string msg = " :";
			if (tokens.size() > 3 && tokens[3].size() != 0)
				msg += tokens[3];
			std::cout << "5\n";
			removefromchannel(channelname, target, "KICK " + channelname + " " + tokens[2] + msg + "\r\n");
			std::cout << "6\n";
			_clients[cc].send_to_user += SERVERNAME" User kicked\r\n";
			return ;
		}
	}
	_clients[cc].send_to_user += SERVERNAME" Channel doesn't exist\r\n";
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