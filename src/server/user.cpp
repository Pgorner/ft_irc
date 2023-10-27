/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:57:15 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/27 11:54:57 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::user(std::vector<std::string> tokens, int cc, int i)
{
	(void)i;
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
		if (tokens.size() == 3)
		{
			if (tokens[2] == "8")
				addmode('i', cc);
			else if (tokens[2] == "2")
				addmode('w', cc);
			if (tokens[2] == "8" || tokens[2] == "2")
				_clients[cc].send_to_user += irc::cEM(irc::RPL_UMODEIS(_clients[cc].mode));
		}
		if (tokens.size() == 5)
		{
			_clients[cc].realname = tokens[4];
			_clients[cc].send_to_user += SERVERNAME " REALNAME has been set to ";
			_clients[cc].send_to_user += tokens[4].c_str();
			_clients[cc].send_to_user += "\r\n";
		}
		else
			_clients[cc].realname = "";
		std::cout << "4\n" << std::endl;
	}
	else if (user == true)
	   	_clients[cc].send_to_user += SERVERNAME " USER has already been taken\r\n" SERVERNAME " Please choose a different one\r\n";
	else
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("USER"));
}