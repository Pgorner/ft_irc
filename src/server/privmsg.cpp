/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/28 19:42:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::sendmsg(std::vector<std::string> tokens, int cc) 
{
	if (tokens.size() == 1)
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("PRIVMSG"));
		return;
	}
	std::stringstream resp;
    for (size_t i = 0; i < _channels.size(); i++) 
	{
		if (!_channels.empty() && _channels[i].name == tokens[1])
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
			for (size_t j = 0; j < _channels[i].members.size(); j++)
			{
				std::cout << _clients[_channels[i].members[j]].nick << std::endl;
				for (size_t k = 0; k < _poll_fds.size(); k++)
				{
					std::cout << "poll fd:" << _poll_fds[k].fd << std::endl;
					if( _poll_fds[k].fd == _clients[_channels[i].members[j]].fd
					&& _clients[_channels[i].members[j]].nick != _clients[cc].nick)
					{
						_clients[_channels[i].members[j]].send_to_user +=  resp.str();
					}
					std::cout << "here\n";
				}
			}
				std::cout << "return\n";
			return ;
		}
	}
	if (tokens[1] != _clients[cc].nick)
	{
		bool found = false;
		resp << ":" << _clients[cc].nick << " PRIVMSG " << tokens[1] << " :";
		for (size_t i = 2; i < tokens.size(); i++)
		{
			resp << tokens[i];
			if (i < tokens.size())
				resp << " ";
		}
		resp << "\r\n";
		for (size_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i].nick == tokens[1])
			{
				found = true;
				std::string response = resp.str();
				_clients[i].send_to_user += response;
			}
		}
		if (found == false)
		{
			logsend(_clients[cc].fd, SERVERNAME " USER NOT FOUND\r\n", cc);
		}
	}
}
