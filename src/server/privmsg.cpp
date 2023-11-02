/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:00:08 by pgorner           #+#    #+#             */
/*   Updated: 2023/11/02 16:58:58 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::broadcastpriv(std::string channelname, std::string msg, int cc)
{
	for(size_t k = 0; k < _clients.size(); k++)
	{
		if (_clients[k]._channels.size() != 0)
		{
			for (size_t j = 0; j < _clients[k]._channels.size(); j++)
			{
				if (_clients[k]._channels[j] == channelname && _clients[k].fd != cc)
					_clients[k].send_to_user += msg;
			}
		}
	}
	write(1, "\n", 1);
	write_nice(WHITE, LINE, true);
}

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
			broadcastpriv(_channels[i].name, resp.str(), cc);
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
