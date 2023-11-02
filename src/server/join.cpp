/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/11/02 17:50:57 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"


void Server::broadcastinchannel(std::string channelname, std::string msg)
{
	for(size_t k = 0; k < _clients.size(); k++)
	{
		if (_clients[k]._channels.size() != 0)
		{
			for (size_t j = 0; j < _clients[k]._channels.size(); j++)
			{
				if (_clients[k]._channels[j] == channelname)
					_clients[k].send_to_user += msg;
			}
		}
	}
	write(1, "\n", 1);
	write_nice(WHITE, LINE, true);
}

bool Server::check_inchannel(int cc, std::string channelname)
{
	for (size_t k = 0; k < _clients[cc]._channels.size(); k++)
	{
		if (_clients[cc]._channels[k] == channelname)
			return(true);
	}
	return(false);
}

int Server::joinchannel(std::vector<std::string> tokens , int cc)
{
	if (!check_params(tokens, 2)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("JOIN")); return 0;}
	if (!(check_tokensize(tokens[1], 2) && tokens[1][0] == '#')){_clients[cc].send_to_user += SERVERNAME" Wrong JOIN parameters\r\n"; return 0;}
	std::string channelname = tokens[1];
	for (size_t i = 0; i < channelname.length(); ++i) channelname[i] = std::tolower(channelname[i]);
	int cnum = find_chan(channelname);
	if (cnum != -1)
	{
		if (check_inchannel(cc, channelname)){ _clients[cc].send_to_user += SERVERNAME" You are already in this channel\r\n"; return 1;}
		bool prot;
		if (string_contains(_channels[cnum].mode, 'i'))
		{
			prot = false;
			for (size_t c = 0; c < _channels[cnum].invited.size(); c++)
				if (_channels[cnum].invited[c] == cc)
					prot = true;
			if (prot == false){return (_clients[cc].send_to_user += SERVERNAME" You have to be invited to join this channel\r\n", 1);}
		}
		if (string_contains(_channels[cnum].mode, 'k'))
		{
			if (!check_params(tokens, 3)){return (_clients[cc].send_to_user += SERVERNAME" This Channel is password protected\r\n", 1);}
			else if (tokens[2] != _channels[cnum].pwd){ return (_clients[cc].send_to_user += SERVERNAME" Incorrect password for channel\r\n", 1);}
		}
		if (string_contains(_channels[cnum].mode, 'l'))
			if (find_ulimit(cnum) >= _channels[cnum].ulimit){ return (_clients[cc].send_to_user += SERVERNAME" This channel has reached the maximum allowed amount of users\r\n", 1);}
		_channels[cnum].members.push_back(cc);
		_clients[cc]._channels.push_back(_channels[cnum].name);
		broadcastinchannel(channelname, ":" + _clients[cc].nick + "!" + _clients[cc].nick + "@localhost" + " JOIN :" + channelname + "\r\n");
		return 1;
	}
	Channel newChannel(channelname, "", "", "", "itkol");
	newChannel.members.push_back(cc);
	_channels.push_back(newChannel);
	_clients[cc]._channels.push_back(newChannel.name);
	_clients[cc].send_to_user += ":" + _clients[cc].nick + "!" + _clients[cc].nick + "@localhost" + " JOIN :" + channelname + "\r\n";
	return 1;
}