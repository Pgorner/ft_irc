/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:57:15 by pgorner           #+#    #+#             */
/*   Updated: 2023/11/03 17:11:55 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::user(std::vector<std::string> tokens, int cc)
{
	if (!check_params(tokens, 2)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("OPER")); return;}
	bool user = false;
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].user == tokens[1])
			user = true;
	}
	if (tokens.size() == 1)
	   	_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("USER"));
	else if (tokens[1].size() < 1)
	    _clients[cc].send_to_user += SERVERNAME " USER too short\r\n";
	else if (tokens.size() > 1 && user == false)
	{
		_clients[cc].user = tokens[1];
	    _clients[cc].send_to_user += SERVERNAME " USER has been set to ";
	    _clients[cc].send_to_user += tokens[1].c_str();
		_clients[cc].send_to_user += "\r\n";
		if (tokens.size() == 5)
		{
			_clients[cc].realname = tokens[4];
			_clients[cc].send_to_user += SERVERNAME " REALNAME has been set to ";
			_clients[cc].send_to_user += tokens[4].c_str();
			_clients[cc].send_to_user += "\r\n";
		}
		else
			_clients[cc].realname = "";
		if (_clients[cc].auth == true)
			_clients[cc].send_to_user += irc::cEM(irc::RPL_WELCOME(_clients[cc].nick, _clients[cc].user, SERVERNAME));
	}
	else if (user == true)
	   	_clients[cc].send_to_user += SERVERNAME " USER has already been taken\r\n" SERVERNAME " Please choose a different one\r\n";
	else
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("USER"));
}