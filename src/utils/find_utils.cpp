/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:34:28 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/28 19:25:09 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool Server::find_user_inchan(int channel, int user)
{
	for (size_t i = 0; i < _channels[channel].members.size(); i++)
	{
		if (_channels[channel].members[i] == user)
			return (true);
	}
	return (false);
}

int Server::find_user(std::string username)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].user == username)
			return (i);
	}
	return (-1);
}

int Server::find_nick(std::string nickname)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == nickname)
			return (i);
	}
	return (-1);
}

int Server::find_ulimit(int i)
{
	int limit = 0;
	for (size_t j = 0; j < _channels[i].members.size(); j++)
		limit++;
	return (limit);
}

int Server::find_chan(std::string channelname)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].name == channelname)
			return (i);
	}
	return (-1);
}