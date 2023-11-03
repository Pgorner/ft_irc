/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:50 by pgorner           #+#    #+#             */
/*   Updated: 2023/11/03 17:45:21 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::quit(size_t i, int cc, std::string msg)
{
    for (size_t j = 0; j < _clients[cc]._channels.size(); j++)
    {
        removefromchannel(_clients[cc]._channels[j], cc, ":" + _clients[cc].nick + " PART :" + _clients[cc]._channels[j] + ":Quitting\r\n");
    }
    for (size_t l = 0; l < _channels.size(); l++)
    {
        for (size_t k = 0; k < _channels[l].members.size(); k++)
        {
            if (_clients[cc].nick == _channels[l].members[k])
            {
                _channels[l].members.erase(_channels[l].members.begin() + k);
            }
        }
    }
    std::string quitMsg = ":" SERVERNAME " 302 " + _clients[cc].nick + " :" + msg + "\r\n";
    logsend(_clients[cc].fd, quitMsg.c_str(), cc);

    close(_clients[cc].fd);
    _clients.erase(_clients.begin() + cc);
    _poll_fds.erase(_poll_fds.begin() + i);
    write_nice(RED, "Client: ", false);
    write_nice(RED, _clients[cc].nick, false);
    write_nice(RED, " disconnected", true);
}