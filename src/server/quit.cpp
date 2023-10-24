/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 14:09:02 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::quit(std::vector<std::string> tokens, size_t i, int cc)
{
	(void)tokens;
	std::string resp = ":"SERVERNAME" 302 " + _clients[cc].nick + " :You have quit the server\r\n";
	logsend(_clients[cc].fd, resp.c_str(), cc);
	for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
		removefromchannel(_clients[cc]._channels[i], cc, "");
    _poll_fds.erase(_poll_fds.begin() + i);
	write_nice(RED, "Client: ", false);
	write_nice(RED, _clients[cc].nick, false);
	write_nice(RED, " disconnected", true);
	_clients.erase(_clients.begin() + cc);
	close(_poll_fds[i].fd);
}