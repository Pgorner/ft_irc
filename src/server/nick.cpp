/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:57:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 15:24:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::nick(std::vector<std::string> tokens, int cc)
{
	if(!check_params(tokens, 2)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("NICK")); return;};
	if(!check_tokensize(tokens[1], 1)){_clients[cc].send_to_user += SERVERNAME " NICK too short\r\n"; return;}
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == tokens[1])
		{
			_clients[cc].send_to_user += SERVERNAME " NICK has already been taken\r\n" SERVERNAME " Please choose a different one\r\n";
			return;	
		}
	}
	_clients[cc].nick = tokens[1];
	_clients[cc].send_to_user += SERVERNAME " NICK has been set to " + tokens[1] + "\r\n";
}