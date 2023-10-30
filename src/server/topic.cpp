/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:58:51 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 15:42:32 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::topic(std::vector<std::string> tokens, int cc)
{
	if (tokens.size() == 1)
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("TOPIC"));
	if (!channelexists(tokens[1]))
		_clients[cc].send_to_user += SERVERNAME" CHANNEL NOT FOUND\r\n";
	int channel = find_chan(tokens[1]);
	if (tokens.size() == 2)
	{
		if (channel != -1)
		{
			if(_channels[channel].topic.empty())
				_clients[cc].send_to_user += irc::cEM(irc::RPL_NOTOPIC(tokens[1]));
			else
				_clients[cc].send_to_user += irc::cEM(irc::RPL_TOPIC(_clients[cc].nick, tokens[1], _channels[channel].topic));
		}
	}
	else if (tokens.size() >= 3)
	{
		if ((_channels[channel].mode.find('t') != std::string::npos
			&& client_oper(cc, find_chan(tokens[1])))
			|| _channels[channel].mode.find('t') == std::string::npos)
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
			_clients[cc].send_to_user += irc::cEM(irc::ERR_CHANOPRIVSNEEDED(tokens[1]));
	}
}