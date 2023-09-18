/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/09/16 18:01:47 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::quit(std::vector<std::string> tokens, size_t i, int cc)
{
	if (tokens.size() > 1 && !tokens[1].empty()) {
	    std::string resp = tokens[1];
	
	    for (size_t i = 2; i < tokens.size(); i++) {
	        if (!tokens[i].empty()) {
	            resp += " " + tokens[i];
	        }
	    }
	    resp += "\r\n";
	    if (i < _poll_fds.size())
	        logsend(_poll_fds[i].fd, resp.c_str(), resp.size());
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