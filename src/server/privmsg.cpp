/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 18:27:44 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::sendmsg(std::vector<std::string> tokens, int cc) 
{
	if (tokens[1].empty())
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("PRIVMSG"));
		return;
	}
	std::stringstream resp;
    for (size_t i = 0; i < _channels.size(); i++) 
	{
		if (_channels[i].name == tokens[1] && !_channels.empty())
		{	
			resp <<  ":" << _clients[cc].nick << "!" << _clients[cc].nick << "@localhost" << " PRIVMSG " << tokens[1] << " :";
			for (size_t h = 2; h < tokens.size(); h++)
				{
					resp << tokens[h];
					if (!tokens[h + 1].empty())
						resp << " ";
				}
				resp << "\r\n";
			for (size_t j = 0; j < _channels[i].members.size(); j++)
			{
				for (size_t k = 0; k < _poll_fds.size(); k++)
				{
					if (_poll_fds[k].fd == _clients[_channels[i].members[j]].fd
						&& _clients[_channels[i].members[j]].nick != _clients[cc].nick)
					{
						_clients[_channels[i].members[j]].send_to_user +=  resp.str();
					}
				}
			}
			return ;
		}
	}
	if (tokens[1] != _clients[cc].nick)
	{
		resp << ":" << _clients[cc].nick << " PRIVMSG " << tokens[1] << " :";
		for (int i = 2; tokens[i].size() != 0; i++)
		{
			resp << tokens[i];
			if (!tokens[i + 1].empty())
				resp << " ";
		}
		resp << "\r\n";
		for (size_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i].nick == tokens[1])
			{
				std::string response = resp.str();
				_clients[i].send_to_user += response;
				for (size_t k = 0; k < _poll_fds.size(); k++)
				{
					if (_poll_fds[k].fd == _clients[i].fd
						&& _clients[i].nick != _clients[cc].nick)
					{
						logsend(_poll_fds[k].fd, _clients[i].send_to_user, cc);
						_clients[i].send_to_user = "";
					}
				}	
			}
		}
	}
}
