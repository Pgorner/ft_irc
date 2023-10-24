/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:56:13 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 14:07:43 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::leavechannel(std::vector<std::string> tokens, int cc)
{
	if (tokens.size() >= 2)
	{
		std::string channelname;
		if (tokens[1].length() >= 2 && tokens[1][0] == '#')
			channelname = tokens[1];
		else
		{
			_clients[cc].send_to_user += SERVERNAME" Wrong channel name format";
			return ;
		}
		removefromchannel(channelname, cc, ":" + _clients[cc].nick + " PART :" + channelname + "\r\n");
	}
	else
		_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("PART");
}