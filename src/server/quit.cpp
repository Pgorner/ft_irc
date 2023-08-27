/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 21:39:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::quit(std::vector<std::string> tokens, int i, int cc)
{
	if (tokens[1].empty() == false)
	{
		std::string resp = tokens[1];
		for (int i = 2; tokens[i].size() != 0; i++)
		{
			resp += tokens[i];
			if (!tokens[i + 1].empty())
				resp += " ";
		}
		resp += "\r\n";
	    logsend(_poll_fds[i].fd, tokens[1].c_str(), cc);
	}
	for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
		removefromchannel(_clients[cc]._channels[i], cc);
	close(_poll_fds[i].fd);
    _poll_fds.erase(_poll_fds.begin() + i);
	write_nice(RED, "Client: ", false);
	write_nice(RED, _clients[cc].realname, false);
	write_nice(RED, " disconnected", true);
	_clients.erase(_clients.begin() + cc);
	close(_poll_fds[i].fd);
}