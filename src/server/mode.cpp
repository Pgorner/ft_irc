/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:50:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 21:37:52 by pgorner          ###   ########.fr       */
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

const char* Server::mode(int cc, std::vector<std::string> tokens){
	if (tokens[1] == _clients[cc].nick)
	{
		if (tokens[2][0] == '-')
		{
			for (int i = 1; tokens[2][i]; i++)
				rmletter(tokens[2][i], cc);	
			return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
		else if (tokens[2][0] == '+')
		{
			for (int i = 1; tokens[2][i]; i++)
			{
				if ((tokens[2][i] != 'o' || tokens[2][i] != 'O' || tokens[2][i] != 'a') &&
					(tokens[2][i] == 'a'
					|| tokens[2][i] == 'i'
					|| tokens[2][i] == 'w'
					|| tokens[2][i] == 'r'
					|| tokens[2][i] == 's'))
					addmode(tokens[2][i], cc);
				if (tokens[2][i] == 'o' || tokens[2][i] == 'O')
					_clients[cc].send_to_user += SERVERNAME" Use OPER cmd to gain priviledges\r\n";
			}
		return (irc::RPL_UMODEIS(_clients[cc].mode));
		}
	}
	else
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
							return(irc::RPL_CHANNELMODEIS(_channels[j].name, _channels[j].mode, _channels[j].modeparams));
						if (tokens[2].find('-') == std::string::npos
							&&  tokens[2].find('+') == std::string::npos)
							return (SERVERNAME" Adding or removing MODES requires +/-\r\n");
						if(_clients[cc].mode.find("o") != std::string::npos
						|| _clients[cc].mode.find("O") != std::string::npos)
						{
							for (size_t k = 1; k < tokens[2].size() && isalpha(tokens[2][k]); k++)
							{
								std::string modes = "it";
								if(tokens[2][1] == 'k')
								{
									if (tokens[2][0] == '+' && tokens[3].empty())
										return (irc::ERR_NEEDMOREPARAMS("MODE"));
									else if (tokens[2][0] == '+')
									{
										if (addchanmode('k', cc, j) > 0)
											return (_channels[j].pwd = tokens[3], SERVERNAME" Password has been added to channel\r\n");
										else
											return (_channels[j].pwd = tokens[3], SERVERNAME" Password has been changed\r\n");
									}
									else if (tokens[2][0] == '-')
									{
										rmchanletter('k', cc, j);
										_channels[j].pwd = "";
										return (SERVERNAME" Password has been removed from channel\r\n");
									}
								}
								if(tokens[2][1] == 'l')
								{
									if ((tokens[2][0] == '+' && tokens[3].empty()) || isAllDigits(tokens[3]) == false)
										return (irc::ERR_NEEDMOREPARAMS("MODE"));
									else if (tokens[2][0] == '+')
									{
										if (addchanmode('l', cc, j) > 0)
											return (_channels[j].ulimit = std::atoi(tokens[3].c_str()), SERVERNAME" Userlimit has been added to channel\r\n");
										else
											return (_channels[j].ulimit = std::atoi(tokens[3].c_str()), SERVERNAME" Userlimit has been changed\r\n");
									}
									else if (tokens[2][0] == '-')
									{
										rmchanletter('l', cc, j);
										_channels[j].ulimit = -1;
										return (SERVERNAME" Userlimit has been removed from channel\r\n");
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
							if (addrm += true)
							{
								std::cout << resp;
								const char* ret = resp.c_str();
								return (ret);
							}
							return(SERVERNAME" Requested MODE/S are not available\r\n");
						}
						else
							return(irc::ERR_NOPRIVILEGES());
					}
				}
			}
		}
		
	}
	return (irc::ERR_USERSDONTMATCH());
}