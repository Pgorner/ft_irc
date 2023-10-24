/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 18:48:00 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::quit(std::vector<std::string> tokens, size_t i, int cc)
{
    (void)tokens;

    for (size_t j = 0; j < _clients[cc]._channels.size(); j++) {
        removefromchannel(_clients[cc]._channels[j], cc, "Quitting");
    }
    std::string quitMsg = ":" SERVERNAME " 302 " + _clients[cc].nick + " :You have quit the server\r\n";
    logsend(_clients[cc].fd, quitMsg.c_str(), cc);

    close(_clients[cc].fd);
    _clients.erase(_clients.begin() + cc);
    _poll_fds.erase(_poll_fds.begin() + i);
    write_nice(RED, "Client: ", false);
    write_nice(RED, _clients[cc].nick, false);
    write_nice(RED, " disconnected", true);
}