/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/11/03 17:34:17 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::broadcastpriv(std::string channelname, std::string msg, int cc)
{
    size_t chan = find_chan(channelname);

    if (chan < _channels.size()) {
        std::vector<int>& members = _channels[chan].members;

        for(size_t k = 0; k < members.size(); k++) {
            size_t memberIndex = members[k];

            if (memberIndex < _clients.size() && memberIndex != static_cast<size_t>(cc)) {
                if (_clients[memberIndex].fd) {
                    _clients[memberIndex].send_to_user += msg;
                }
            }
        }
    }
}


void Server::sendmsg(std::vector<std::string> tokens, int cc) 
{
	if (!check_params(tokens, 2))
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("PRIVMSG"));
		return;
	}
	std::stringstream resp;
	if (channelexists(tokens[1]))
	{
			bool inc = false;
			std::vector<std::string>& channels = _clients[cc]._channels;
			for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end();)
			{
			    if (*it == tokens[1])
					inc = true;
			    ++it;
			}
			if (inc == false)
				return ;
			resp <<  ":" << _clients[cc].nick << "!" << _clients[cc].nick << "@localhost" << " PRIVMSG " << tokens[1] << " :";
			for (size_t h = 2; h < tokens.size(); h++)
			{
				resp << tokens[h];
				if (h < tokens.size())
					resp << " ";
			}
			resp << "\r\n";
			broadcastpriv(tokens[1], resp.str(), cc);
			return ;
		
	}
	else if (find_nick(tokens[1]) != -1)
	{
		if (tokens[1] != _clients[cc].nick)
		{
			resp << ":" << _clients[cc].nick << " PRIVMSG " << tokens[1] << " :";
			for (size_t i = 2; i < tokens.size(); i++)
			{
				resp << tokens[i];
				if (i < tokens.size())
					resp << " ";
			}
			resp << "\r\n";
			std::string response = resp.str();
			_clients[find_nick(tokens[1])].send_to_user += response;
		}
		else if (tokens[1] != _clients[cc].nick)
			logsend(_clients[cc].fd, SERVERNAME " CANNOT SEND MSG TO URSELF\r\n", cc);
	}
}