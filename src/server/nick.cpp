/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:57:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/27 16:10:08 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"


void Server::nick(std::vector<std::string> tokens, int cc, int i)
{
	(void)i;
	bool nickinuse = false;
	if (tokens[1].empty() == true)
	{
	   	_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("NICK"));
		return;
	}
	else if (tokens[1].size() < 1)
	{
	    _clients[cc].send_to_user += SERVERNAME " NICK too short\r\n";
		return;
	}
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == tokens[1])
			nickinuse = true;
	}
	if (tokens.size() > 1 && nickinuse == false)
	{
	    _clients[cc].nick = tokens[1];
	    _clients[cc].send_to_user += SERVERNAME " NICK has been set to ";
	    _clients[cc].send_to_user += tokens[1].c_str();
		_clients[cc].send_to_user += "\r\n";
	}
	else if (nickinuse == true)
	   	_clients[cc].send_to_user += SERVERNAME " NICK has already been taken\r\n" SERVERNAME " Please choose a different one\r\n";
}