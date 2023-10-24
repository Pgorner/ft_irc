/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:50:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 15:45:52 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Server::addmode(char letter, int cc){
	if(_clients[cc].mode.find(letter) == std::string::npos)
	{
		_clients[cc].mode += letter;
	}
}

int Server::addchanmode(char letter, int cc, int channel)
{
	if(_channels[channel].mode.find(letter) == std::string::npos)
		_channels[channel].mode += letter;
	else
	{
		_clients[cc].send_to_user += SERVERNAME" Cannot add MODE \"";
		_clients[cc].send_to_user += letter;
		_clients[cc].send_to_user += "\" as it is already active\r\n";
		return -1;
	}
	return 1;
}

void Server::handleOpermode(int cc, std::vector<std::string> tokens)
{
	for (size_t user = 0; user < _clients.size(); user++)
	{
		if (_clients[user].nick == tokens[1])
		{
			if (tokens[2][0] == '-')
			{
				for (int i = 1; tokens[2][i]; i++)
					rmletter(tokens[2][i], user);	
				_clients[user].send_to_user += irc::RPL_UMODEIS(_clients[user].mode);
				return;
			}
			else if (tokens[2][0] == '+')
			{
				for (int i = 1; tokens[2][i]; i++)
				{
					if ((tokens[2][i] == 'o' 
						|| tokens[2][i] == 'O'
						|| tokens[2][i] == 'a'
						|| tokens[2][i] == 'i'
						|| tokens[2][i] == 'w'
						|| tokens[2][i] == 'r'
						|| tokens[2][i] == 's'))
						addmode(tokens[2][i], user);
				}
			_clients[user].send_to_user += irc::RPL_UMODEIS(_clients[user].mode);
			}
		_clients[cc].send_to_user += "You have changed " + _clients[user].nick + "\'s Mode\r\n";
		}
	}
}
void Server::userMode(int cc, std::vector<std::string> tokens)
{
	if (tokens[1] != _clients[cc].nick)
		handleOpermode(cc, tokens);
	if (tokens[2][0] == '-')
	{
		for (int i = 1; tokens[2][i]; i++)
			rmletter(tokens[2][i], cc);	
		_clients[cc].send_to_user += irc::RPL_UMODEIS(_clients[cc].mode);
		return;
	}
	else if (tokens[2][0] == '+')
	{
		for (int i = 1; tokens[2][i]; i++)
		{
			if ((tokens[2][i] != 'o' 
				&& tokens[2][i] != 'O'
				&& tokens[2][i] != 'a') 
				&& (tokens[2][i] == 'a'
				|| tokens[2][i] == 'i'
				|| tokens[2][i] == 'w'
				|| tokens[2][i] == 'r'
				|| tokens[2][i] == 's'))
				addmode(tokens[2][i], cc);
			if (tokens[2][i] == 'O' || tokens[2][i] == 'o')
				_clients[cc].send_to_user += SERVERNAME" Use OPER cmd to gain priviledges\r\n";
		}
	_clients[cc].send_to_user += irc::RPL_UMODEIS(_clients[cc].mode);
	}
}

int Server::channelMode(int cc, std::vector<std::string> tokens)
{
	for(std::vector<std::string>::size_type i = 0; i < _clients[cc]._channels.size(); i++)
	{
		if (_clients[cc]._channels[i] == tokens[1])
		{
			for(std::vector<std::string>::size_type j = 0; j < _channels.size(); j++)
			{
				if (_clients[cc]._channels[i] == _channels[j].name)
				{
					bool addrm = false;
					std::string resp = "";
					if (tokens.size() == 2)
						return(_clients[cc].send_to_user += irc::RPL_CHANNELMODEIS(_channels[j].name, _channels[j].mode, _channels[j].modeparams), 0);
					if (tokens[2].find('-') == std::string::npos
						&&  tokens[2].find('+') == std::string::npos)
						return (_clients[cc].send_to_user += SERVERNAME" Adding or removing MODES requires +/-\r\n", 0);
					if(_clients[cc].mode.find("o") != std::string::npos
					|| _clients[cc].mode.find("O") != std::string::npos)
					{
						for (size_t k = 1; k < tokens[2].size() && isalpha(tokens[2][k]); k++)
						{
							std::string modes = "it";
							if(tokens[2][1] == 'k')
							{
								if (tokens[2][0] == '+' && tokens[3].empty())
									return (_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("MODE"), 0);
								else if (tokens[2][0] == '+')
								{
									if (addchanmode('k', cc, j) > 0)
										return (_channels[j].pwd = tokens[3], _clients[cc].send_to_user += SERVERNAME" Password has been added to channel\r\n", 0);
									else
										return (_channels[j].pwd = tokens[3], _clients[cc].send_to_user += SERVERNAME" Password has been changed\r\n", 0);
								}
								else if (tokens[2][0] == '-')
								{
									rmchanletter('k', cc, j);
									_channels[j].pwd = "";
									return (_clients[cc].send_to_user += SERVERNAME" Password has been removed from channel\r\n", 0);
								}
							}
							if(tokens[2][1] == 'l')
							{
								if ((tokens[2][0] == '+' && tokens[3].empty()) || isAllDigits(tokens[3]) == false)
									return (_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("MODE"), 0);
								else if (tokens[2][0] == '+')
								{
									if (addchanmode('l', cc, j) > 0)
										return (_channels[j].ulimit = std::atoi(tokens[3].c_str()), _clients[cc].send_to_user += SERVERNAME" Userlimit has been added to channel\r\n", 0);
									else
										return (_channels[j].ulimit = std::atoi(tokens[3].c_str()), _clients[cc].send_to_user += SERVERNAME" Userlimit has been changed\r\n", 0);
								}
								else if (tokens[2][0] == '-')
								{
									rmchanletter('l', cc, j);
									_channels[j].ulimit = -1;
									return (_clients[cc].send_to_user += SERVERNAME" Userlimit has been removed from channel\r\n", 0);
								}
							}
							else if (modes.find(tokens[2][k]) != std::string::npos)
								{
									addrm = true;
									if (tokens[2][0] == '+')
									{
										if(addchanmode(tokens[2][k], cc, j) > 0)
										{
											resp += SERVERNAME" Added mode ";
											resp += tokens[2][k];
											resp += " to channel\r\n";
										}
									}
									else if (tokens[2][0] == '-')
									{
										if (rmchanletter(tokens[2][k], cc, j) > 0)
										{
											resp += SERVERNAME" Removed mode ";
											resp += tokens[2][k];
											resp += " from channel\r\n";
										}
									}
								}
						}
						if (addrm)
							return (_clients[cc].send_to_user += resp.c_str(), 0);
						return(_clients[cc].send_to_user += SERVERNAME" Requested MODE/S are not available\r\n", 0);
					}
					else
						return(_clients[cc].send_to_user += irc::ERR_NOPRIVILEGES(), 0);
				}
			}
		}
	}
	return(_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("MODE"), 0);
}

int Server::userexists(std::string username)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == username)
		{
			return (1);
		}
	}
	return (0);
}

int Server::mode(int cc, std::vector<std::string> tokens)
{
	if (tokens[1].empty() == true)
		return(_clients[cc].send_to_user += irc::RPL_UMODEIS(_clients[cc].mode), 0);
	else if (tokens[1].empty() && tokens[2].empty())
		return(_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("MODE"), 0);
	if (tokens[1] == _clients[cc].nick || (userexists(tokens[1]) && _clients[cc].mode.find("O")))
		return(userMode(cc, tokens), 0);
	else
		return(channelMode(cc, tokens), 0);
	return (_clients[cc].send_to_user += irc::ERR_USERSDONTMATCH(), 0);
}