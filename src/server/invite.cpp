/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:58:34 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 21:40:13 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::invite(std::vector<std::string> tokens, int cc)
{
	if (_clients[cc].mode.find("O") != std::string::npos)
	{
		if (tokens.size() != 3)
			_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("INVITE");
		else
		{
			int invnick = find_nick(tokens[2]);
			if (invnick != -1)
			{
				_clients[invnick].send_to_user += irc::RPL_INVITING(_clients[cc].nick, _clients[invnick].nick, tokens[1]);
				_clients[cc].send_to_user += irc::RPL_INVITING(_clients[cc].nick, _clients[invnick].nick, tokens[1]);
				_channels[find_chan(tokens[1])].invited.push_back(invnick);
			}
			else
				_clients[cc].send_to_user += SERVERNAME" USER NOT FOUND\r\n";
		}
	}
	else
		_clients[cc].send_to_user += irc::ERR_CHANOPRIVSNEEDED(tokens[1]);
}