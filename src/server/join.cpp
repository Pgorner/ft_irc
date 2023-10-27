/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:52:17 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/27 11:23:34 by pgorner          ###   ########.fr       */
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

int Server::joinchannel(std::vector<std::string> tokens , int cc)
{
	if (tokens.size() == 2 || tokens.size() == 3)
	{
		std::string channelname;
		if (tokens[1].length() >= 2 && tokens[1][0] == '#')
			channelname = tokens[1];
		else
		{
			std::cout << "Wrong channel name format" << std::endl;
			return 0;
		}
		for (size_t i = 0; i < _channels.size(); i++)
		{
			if (_channels[i].name == channelname)
			{
				for (size_t k = 0; k < _clients[cc]._channels.size(); k++)
				{
					std::cout << _clients[cc]._channels[k] << std::endl;
					if (_clients[cc]._channels[k] == channelname)
					{
						_clients[cc].send_to_user += SERVERNAME" You are already in this channel\r\n";
						return 1;
					}
				}
				bool prot = true;
				if (_channels[i].mode.find('i') != std::string::npos)
				{
					prot = false;
					for (size_t c = 0; c < _channels[i].invited.size(); c++)
						if (_channels[i].invited[c] == cc)
							prot = true;
				}
				if (_channels[i].mode.find('k') != std::string::npos)
				{
					if (tokens.size() == 2)
						return (_clients[cc].send_to_user += SERVERNAME" This Channel is password protected\r\n", 1);
					else if (tokens[2] != _channels[i].pwd)
						return (_clients[cc].send_to_user += SERVERNAME" Incorrect password for channel\r\n", 1);
				}
				if (_channels[i].mode.find('l') != std::string::npos)
				{
					if (find_ulimit(i) >= _channels[i].ulimit)
						return (_clients[cc].send_to_user += SERVERNAME" This channel has reached the maximum allowed amount of users\r\n", 1);
				}
				if (prot == false)
					return (_clients[cc].send_to_user += SERVERNAME" You have to be invited to join this channel\r\n", 1);
				_channels[i].members.push_back(cc);
				_clients[cc]._channels.push_back(_channels[i].name);
				broadcastinchannel(channelname, ":" + _clients[cc].nick + "!" + _clients[cc].nick + "@localhost" + " JOIN :" + channelname + "\r\n");
				return 1;
			}
		}
		Channel newChannel(channelname, "", "", "", "itkol");
		newChannel.members.push_back(cc);
		_channels.push_back(newChannel);
		_clients[cc]._channels.push_back(newChannel.name);
		_clients[cc].send_to_user += ":" + _clients[cc].nick + "!" + _clients[cc].nick + "@localhost" + " JOIN :" + channelname + "\r\n";
		return 1;
	}
	else
	{
		_clients[cc].send_to_user += SERVERNAME" Wrong JOIN parameters\r\n";
		return 0;
	}
}