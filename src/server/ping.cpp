/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:52:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 16:12:08 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/irc.hpp"

void Server::ping(std::vector<std::string> tokens,int cc)
{
	_clients[cc].send_to_user += "PONG " + _clients[cc].nick;
	for(size_t i = 2; i <= tokens.size(); i++)
		_clients[cc].send_to_user += " " + tokens[i];
	_clients[cc].send_to_user += "\r\n";
}

void Server::pong(int cc)
{
	if (_clients[cc].ping == false)
		_clients[cc].ping = true;
}
