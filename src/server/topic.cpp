/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:58:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 18:28:12 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::topic(std::vector<std::string> tokens, int cc)
{
	if (tokens.size() == 1)
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("TOPIC"));
	else if (tokens.size() == 2)
	{
		int channel = find_chan(tokens[1]);
		if (channel != -1)
		{
			if(_channels[channel].topic.empty())
				_clients[cc].send_to_user += irc::cEM(irc::RPL_NOTOPIC(tokens[1]));
			else
				_clients[cc].send_to_user += irc::cEM(irc::RPL_TOPIC(_clients[cc].nick, tokens[1], _channels[channel].topic));
		}
		else
			_clients[cc].send_to_user += SERVERNAME" CHANNEL NOT FOUND\r\n";
	}
	else if (tokens.size() >= 3)
	{
		int channel = find_chan(tokens[1]);
		if ((_channels[channel].mode.find('t') != std::string::npos
			&& _clients[cc].mode.find('O') != std::string::npos)
			|| _channels[channel].mode.find('t') == std::string::npos)
			{
				if (channel != -1)
				{
					std::string topic;
					for(size_t t = 2; t < tokens.size(); t++)
					{
						topic += tokens[t];
						if (!tokens[t].empty())
							topic += " ";
					}
					_channels[channel].topic = topic;
					_clients[cc].send_to_user += irc::cEM(irc::RPL_TOPIC(_clients[cc].nick, tokens[1], topic));
				}
				else
					_clients[cc].send_to_user += SERVERNAME" CHANNEL NOT FOUND\r\n";
			}
		else
			_clients[cc].send_to_user += irc::cEM(irc::ERR_CHANOPRIVSNEEDED(tokens[1]));
	}
}