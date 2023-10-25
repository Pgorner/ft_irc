/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:59:28 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 18:27:05 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::names(std::vector<std::string> tokens, int cc)
{
	std::string nicklist = "";
	for(int i = 0; _channels[i].name.size() != 0; i++)
	{
		if (_channels[i].name == tokens[1])
		{
			for(size_t j = 0; j < _channels[i].members.size(); j++)
			{
				nicklist += _clients[_channels[i].members[j]].nick;
				if (_channels[i].members[j + 1])
					nicklist += " ";
			}
		}
	}
	_clients[cc].send_to_user += irc::cEM(irc::RPL_NAMREPLY(tokens[1], nicklist));
	_clients[cc].send_to_user += irc::cEM(irc::RPL_ENDOFNAMES(tokens[1]));
}