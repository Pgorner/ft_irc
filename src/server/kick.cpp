/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:55:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 18:04:03 by pgorner          ###   ########.fr       */
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
		_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("KICK");
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
					removefromchannel(channelname, cc, "KICK " + channelname + " " + tokens[2] + msg + "\r\n");
					_clients[cc].send_to_user += SERVERNAME" User kicked\r\n";
					// std::vector<int>& members = _channels[i].members;
					// std::vector<int>::iterator it = members.begin();
					// while (it != members.end()) {
					//     if (*it == target) {
					//         it = members.erase(it);
					//     } else {
					//         ++it;
					//     }
					// }
					// std::vector<std::string>& channels= _clients[target]._channels;
					// std::vector<std::string>::iterator here = channels.begin();
					// while (here != channels.end()) {
					//     if (*here == channelname) {
					//         here = channels.erase(here);
					//     } else {
					//         ++here;
					//     }
					// }
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
		_clients[cc].send_to_user += irc::ERR_CHANOPRIVSNEEDED(tokens[1]);
}

void Server::removefromchannel(std::string channelname, int cc, std::string msg)
{
	if (msg.size() != 0)
		broadcastinchannel(channelname, msg);
	for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
	{
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
			return ;
		}
	}
	_clients[cc].send_to_user += SERVERNAME" User is not found in the channel\r\n";
}	