/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:58:34 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 16:06:13 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::invite(std::vector<std::string> tokens, int cc)
{
	if(!check_params(tokens, 3)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("INVITE")); return;};
	if (!channelexists(tokens[1])){_clients[cc].send_to_user += SERVERNAME" Channel not found\r\n"; return;};
	if (client_oper(cc, find_chan(tokens[1])))
	{
		int invnick = find_nick(tokens[2]);
		if (invnick != -1)
		{
			_clients[invnick].send_to_user += irc::cEM(irc::RPL_INVITING(_clients[cc].nick, _clients[invnick].nick, tokens[1]));
			_clients[cc].send_to_user += irc::cEM(irc::RPL_INVITING(_clients[cc].nick, _clients[invnick].nick, tokens[1]));
			_channels[find_chan(tokens[1])].invited.push_back(invnick);
		}
		else
			_clients[cc].send_to_user += SERVERNAME" USER NOT FOUND\r\n";
		return;
	}
	_clients[cc].send_to_user += irc::cEM(irc::ERR_CHANOPRIVSNEEDED(tokens[1]));
}